#include <views/Menu.h>

Menu::MenuAction Menu::handleClick(int x, int y) {
  std::list<MenuItem>::iterator it;

  for (it = _menu_items.begin(); it != _menu_items.end(); ++it) {
    sf::IntRect menu_item_rect = it->rect;
    
    if ((menu_item_rect.top + menu_item_rect.height) > y
      && menu_item_rect.top < y
      && menu_item_rect.left < x
      && (menu_item_rect.left + menu_item_rect.width) > x) {
      return it->action;
    }
  }  
  return NOTHING;
}