#include "Textbox.h"

Textbox::Textbox(const sf::Font& font, const sf::Vector2f& size, const sf::Vector2f& position): text(font) {
    box.setSize(size);
    box.setFillColor(sf::Color(0, 0, 0, 200));
    box.setPosition(position);

    //text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setPosition(position + sf::Vector2f(10, 10));
}

void Textbox::setLines(const std::vector<std::string>& newLines) {
    lines = newLines;
    currentLine = 0;
    if (!lines.empty()) {
        std::string wrapped = wrapText(lines[0], text.getFont(), text.getCharacterSize(), box.getSize().x - 20.f);
        text.setString(wrapped);
        show();
    }
}

void Textbox::show() { visible = true; }
void Textbox::hide() { visible = false; }

void Textbox::next() {
    if (++currentLine >= lines.size()) {
        hide();
    }
    else {
        std::string wrapped = wrapText(lines[currentLine], text.getFont(), text.getCharacterSize(), box.getSize().x - 20.f);
        text.setString(wrapped);
    }
}

bool Textbox::isVisible() const { return visible; }
bool Textbox::isFinished() const { return currentLine >= lines.size(); }

void Textbox::draw(sf::RenderWindow& window) {
    if (!visible) return;
    window.draw(box);
    window.draw(text);
}

std::string Textbox::wrapText(const std::string& input, const sf::Font& font, unsigned int characterSize, float maxWidth) {
    std::istringstream iss(input);
    std::string word;
    std::string line, result;

    sf::Text testText(font, "", characterSize);

    while (iss >> word) {
        std::string trial = line + (line.empty() ? "" : " ") + word;
        testText.setString(trial);

        if (testText.getLocalBounds().size.x > maxWidth) {
            result += line + "\n";
            line = word;
        }
        else {
            line = trial;
        }
    }

    result += line;
    return result;
}
