#include "Menu.h"
#include <assert.h>

namespace ArkanoidGame
{
	void Menu::Init(const MenuItem& item)
	{
		rootItem = item;

		InitMenuItem(rootItem);
		if (!rootItem.childrens.empty()) {
			SelectMenuItem(rootItem.childrens.front());
		}
	}
	
	void Menu::InitMenuItem(MenuItem& item)
	{
		for (auto& child : item.childrens)
		{
			child.parent = &item;
			InitMenuItem(child);
		}
	}

	void Menu::Draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin)
	{
		MenuItem& expandedItem = GetCurrentContext();

		std::vector<sf::Text*> texts;
		texts.reserve(expandedItem.childrens.size());
		for (auto& child : expandedItem.childrens) {
			if (child.isEnabled) {
				texts.push_back(&child.text);
			}
		}

		DrawTextList(
			window,
			texts,
			expandedItem.childrenSpacing,
			expandedItem.childrenOrientation,
			expandedItem.childrenAlignment,
			position,
			origin);
	}
	
	void Menu::PressOnSelectedItem()
	{
		if (!selectedItem) {
			return;
		}

		if (selectedItem->onPressCallback) {
			selectedItem->onPressCallback(*selectedItem);
			return;
		}

		// default behaviour
		if (!selectedItem->childrens.empty()) {
			SelectMenuItem(selectedItem->childrens.front());
		}
	}

	void Menu::GoBack()
	{
		MenuItem& parent = GetCurrentContext();
		if (&parent != &rootItem) {
			SelectMenuItem(parent);
		}
	}

	void Menu::SwitchToPreviousMenuItem()
	{
		if (!selectedItem) {
			return;
		}
		
		MenuItem* parent = selectedItem->parent;
		assert(parent); // There always should be parent

		auto it = std::find_if(parent->childrens.begin(), parent->childrens.end(), [this](const auto& item) {
			return selectedItem == &item;
		});
		if (it != parent->childrens.begin()) {
			SelectMenuItem(*std::prev(it));
		}
	}

	void Menu::SwitchToNextMenuItem()
	{
		if (!selectedItem) {
			return;
		}
		
		MenuItem* parent = selectedItem->parent;
		assert(parent); // There always should be parent
		
		auto it = std::find_if(parent->childrens.begin(), parent->childrens.end(), [this](const auto& item) {
			return selectedItem == &item;
			});
		it = std::next(it);
		if (it != parent->childrens.end()) {
			SelectMenuItem(*it);
		}
	}

	void Menu::SelectMenuItem(MenuItem& item)
	{
		assert(&item != &rootItem);

		if (selectedItem == &item)
		{
			return;
		}

		if (!item.isEnabled)
		{
			// Don't allow to select disabled item
			return;
		}

		if (selectedItem)
		{
			selectedItem->text.setFillColor(selectedItem->deselectedColor);
		}

		selectedItem = &item;

		if (selectedItem)
		{
			selectedItem->text.setFillColor(selectedItem->selectedColor);
		}
	}

	MenuItem& Menu::GetCurrentContext()
	{
		return selectedItem ? *(selectedItem->parent) : rootItem;
	}
}
