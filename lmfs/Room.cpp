#include "Room.h"

constexpr int TILE_SIZE = 32;
constexpr int ROOM_WIDTH = 20;
constexpr int ROOM_HEIGHT = 16;

Room::Room(const std::string& layoutFile, const std::string& graphicsFile, bool completed) : completed(completed) {
    loadLayout(layoutFile, completed);
    loadGraphics(graphicsFile);
    srand(time(0));
}

Room::~Room()
{
    // Clean up doors vector
    for (auto p : doors) {
        delete p;
    }
    // Clean up collisions
    for (auto p : collisionRects) {
        delete p;
    }
}

void Room::loadLayout(const std::string& layoutFile, bool completed) {
    std::ifstream file(layoutFile);
    if (!file.is_open()) {
        std::cerr << "Failed to open layout file: " << layoutFile << std::endl;
        return;
    }

    // Load collision info
    std::string line;
    for (int y = 0; y < ROOM_HEIGHT && std::getline(file, line); ++y) {
        if (line == "doors") break;
        std::istringstream ss(line);
        for (int x = 0; x < ROOM_WIDTH; ++x) {
            int value;
            ss >> value;
            if (value == 1) {
                collisionRects.push_back(new sf::FloatRect(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE), sf::Vector2f(TILE_SIZE, TILE_SIZE)));
            }
        }
    }     

    // Load doors
    while (std::getline(file, line)) {
        if (line == "enemies") break;
        std::istringstream iss(line);
        float x, y, w, h, destX, destY;
        int destRoom, type;
        if (iss >> x >> y >> w >> h >> destRoom >> destX >> destY >> type) {
            doors.push_back(new Door(sf::Vector2f(x, y), w, h, destRoom, sf::Vector2f(destX, destY), type));
            if (completed || type == -1) doors.back()->open = true;
            else doors.back()->open = false;
        }
    }

    // Load enemies
    if (!completed) {
        eManager = new EnemyManager(collisionRects);
        while (std::getline(file, line)) {
            if (line == "end") break;
            std::istringstream iss(line);
            float x, y;
            int type, dropId, dropCount;
            bool priority;
            if (iss >> x >> y >> type >> priority >> dropId >> dropCount) {
                eManager->enemies.push_back(new Enemy(sf::Vector2f(x, y), type, dropId, dropCount, priority));
                //doors.push_back(new Door(sf::Vector2f(x, y), w, h, destRoom, sf::Vector2f(destX, destY)));
                //if (completed) doors.back()->open = true;
                //else doors.back()->open = false;
            }
        }
    }
    
}

void Room::loadGraphics(const std::string& graphicsFile) {
    std::ifstream file(graphicsFile);
    if (!file.is_open()) {
        std::cerr << "Failed to open graphics file: " << graphicsFile << std::endl;
        return;
    }

    std::string textureFilename;
    std::getline(file, textureFilename);

    if (!tileset.loadFromFile("assets/" + textureFilename)) {
        std::cerr << "Failed to load texture: " << textureFilename << std::endl;
        return;
    }
    
    std::string line;
    for (int y = 0; y < ROOM_HEIGHT && std::getline(file, line); ++y) {
        if (line == "doors") break;
        std::istringstream ss(line);
        for (int x = 0; x < ROOM_WIDTH; ++x) {
            std::string token;
            ss >> token;

            // Skip empty tiles
            if (token == "-")
                continue;

            // Expecting format row,col (1-based index)
            size_t comma = token.find(',');
            if (comma == std::string::npos)
                continue;

            int row = std::stoi(token.substr(0, comma)) - 1;
            int col = std::stoi(token.substr(comma + 1)) - 1;

            sf::RectangleShape tileShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            tileShape.setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
            tileShape.setTexture(&tileset);
            tileShape.setTextureRect(sf::IntRect(sf::Vector2i(col * TILE_SIZE, row * TILE_SIZE), sf::Vector2i(TILE_SIZE, TILE_SIZE)));

            tiles.push_back(tileShape);
        }
    }
    
    // LOAD DOOR INFO
    while (std::getline(file, line)) {
        if (line == "doors") {
            std::string text1, text2;
            file >> text1 >> text2;

            // Get texture data for open and closed door
            size_t comma1 = text1.find(',');
            if (comma1 == std::string::npos)
                continue;

            int row1 = std::stoi(text1.substr(0, comma1)) - 1;
            int col1 = std::stoi(text1.substr(comma1 + 1)) - 1;

            size_t comma2 = text2.find(',');
            if (comma2 == std::string::npos)
                continue;

            int row2 = std::stoi(text2.substr(0, comma2)) - 1;
            int col2 = std::stoi(text2.substr(comma2 + 1)) - 1;


            for (auto p : doors) {
                p->shape.setTexture(&tileset);
                if(p->open) p->shape.setTextureRect(sf::IntRect(sf::Vector2i(col2 * TILE_SIZE, row2 * TILE_SIZE), sf::Vector2i(TILE_SIZE, TILE_SIZE)));
                else {
                    p->shape.setTextureRect(sf::IntRect(sf::Vector2i(col1 * TILE_SIZE, row1 * TILE_SIZE), sf::Vector2i(TILE_SIZE, TILE_SIZE)));
                    p->secondaryShape.setTextureRect(sf::IntRect(sf::Vector2i(col2 * TILE_SIZE, row2 * TILE_SIZE), sf::Vector2i(TILE_SIZE, TILE_SIZE)));
                }
            }
        }
    }
    
}

void Room::render(sf::RenderWindow& window) const {
    for (const auto& tile : tiles) {
        window.draw(tile);
    }
    for (const auto& door : doors) {
        window.draw(door->shape);
    }
    if (eManager != nullptr) eManager->render(window);
}

bool Room::update(const float& delTime)
{
    if (eManager != nullptr) {
        if (eManager->update(delTime)) {
            complete();
        }
    }
    return completed;
}

void Room::complete()
{
    completed = true;
    for (auto p : doors) {
        if (p->type == 0) {
            p->open = true;
        }
        else continue;
    }
}

const std::vector<sf::FloatRect*>& Room::getCollisionRects() const {
    return collisionRects;
}

EnemyManager* Room::getEManager()
{
    return eManager;
}

