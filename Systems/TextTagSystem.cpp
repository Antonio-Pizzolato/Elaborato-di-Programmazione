//
// Created by Antonio on 18/02/2022.
//

#include "TextTagSystem.h"


//Private functions
void TextTagSystem::initVariables()
{

}

void TextTagSystem::initFonts(std::string font_file)
{
    if (!font.loadFromFile(font_file))
        std::cout << "ERROR::TEXTTAGSYSTEM::CONSTRUCTOR::Failed to load font " << font_file << "\n";
}

void TextTagSystem::initTagTemplates()
{
    tagTemplates[DEFAULT_TAG] = new TextTag(font, "", 100.f, 100.f, 0.f, -1.f, sf::Color::White, 25, 100.f, true, 200.f, 200.f, 2);
    tagTemplates[NEGATIVE_TAG] = new TextTag(font, "", 100.f, 100.f, 0.f, 1.f, sf::Color::Red, 25, 100.f, true, 200.f, 200.f, 1);
    tagTemplates[EXPERIENCE_TAG] = new TextTag(font, "", 100.f, 100.f, 0.f, -1.f, sf::Color::Cyan, 30, 200.f, true, 200.f, 200.f, 2);
}

//Constructor / Destructor
TextTagSystem::TextTagSystem(std::string font_file)
{
    initFonts(font_file);
    initVariables();
    initTagTemplates();
}

TextTagSystem::~TextTagSystem()
{
    //Clean up tags
    for (auto *tag : tags)
    {
        delete tag;
    }

    //Clean up templates
    for (auto &tag : tagTemplates)
    {
        delete tag.second;
    }
}

//Functions
void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const std::string str, const std::string prefix = "", const std::string postfix = "")
{
    std::stringstream ss;
    ss << prefix << " " << str << " " << postfix;
    tags.push_back(new TextTag(tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const int i, const std::string prefix = "", const std::string postfix = "")
{
    std::stringstream ss;
    ss << prefix << " " << i << " " << postfix;
    tags.push_back(new TextTag(tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const float f, const std::string prefix = "", const std::string postfix = "")
{
    std::stringstream ss;
    ss << prefix << " " << f << " " << postfix;
    tags.push_back(new TextTag(tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::update(float timeDelta)
{
    for (size_t i = 0; i < tags.size(); ++i)
    {
        tags[i]->update(timeDelta);

        if (tags[i]->isExpired())
        {
            delete tags[i];
            tags.erase(tags.begin() + i);
        }
    }
}

void TextTagSystem::render(sf::RenderTarget & target)
{
    for (auto&tag : tags)
    {
        tag->render(target);
    }
}