/*
 *   Copyright (c) 2008-2018 SLIBIO <https://github.com/SLIBIO>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 */

#include "slib/ui/menu.h"

namespace slib
{
	SLIB_DEFINE_OBJECT(MenuItem, Object)
	
	MenuItem::MenuItem()
	{
		m_flagEnabled = sl_true;
		m_flagChecked = sl_false;
	}
	
	MenuItem::~MenuItem()
	{
	}

	Ref<Menu> MenuItem::getParent() const
	{
		return m_parent;
	}
	
	String MenuItem::getText() const
	{
		return m_text;
	}
	
	void MenuItem::setText(const String& text)
	{
		m_text = text;
	}
	
	const KeycodeAndModifiers& MenuItem::getShortcutKey() const
	{
		return m_shortcutKey;
	}
	
	void MenuItem::setShortcutKey(const KeycodeAndModifiers& km)
	{
		m_shortcutKey = km;
	}
	
	const KeycodeAndModifiers& MenuItem::getSecondShortcutKey() const
	{
		return m_secondShortcutKey;
	}
	
	void MenuItem::setSecondShortcutKey(const KeycodeAndModifiers& km)
	{
		m_secondShortcutKey = km;
	}
	
	sl_bool MenuItem::isEnabled() const
	{
		return m_flagEnabled;
	}
	
	void MenuItem::setEnabled(sl_bool flag)
	{
		m_flagEnabled = flag;
	}
	
	sl_bool MenuItem::isChecked() const
	{
		return m_flagChecked;
	}
	
	void MenuItem::setChecked(sl_bool flag)
	{
		m_flagChecked = flag;
	}
	
	Ref<Bitmap> MenuItem::getIcon() const
	{
		return m_icon;
	}
	
	void MenuItem::setIcon(const Ref<Bitmap>& icon)
	{
		m_icon = icon;
	}
	
	Ref<Bitmap> MenuItem::getCheckedIcon() const
	{
		return m_checkedIcon;
	}
	
	void MenuItem::setCheckedIcon(const Ref<Bitmap>& icon)
	{
		m_checkedIcon = icon;
	}
	
	Ref<Menu> MenuItem::getSubmenu() const
	{
		return m_submenu;
	}
	
	void MenuItem::setSubmenu(const Ref<Menu>& menu)
	{
		m_submenu = menu;
	}
	
	Function<void()> MenuItem::getAction() const
	{
		return m_action;
	}
	
	void MenuItem::setAction(const Function<void()>& action)
	{
		m_action = action;
	}
	
	sl_bool MenuItem::isSeparator() const
	{
		return sl_false;
	}
	
	class _priv_MenuItemSeparator : public MenuItem
	{
	public:
		sl_bool isSeparator() const override
		{
			return sl_true;
		}
		
	};
	
	Ref<MenuItem> MenuItem::createSeparator()
	{
		return new _priv_MenuItemSeparator;
	}
	
	sl_bool MenuItem::processShortcutKey(const KeycodeAndModifiers& km)
	{
		if (km != 0) {
			if (km == m_shortcutKey) {
				m_action();
				return sl_true;
			}
			Ref<Menu> submenu = m_submenu;
			if (submenu.isNotNull()) {
				return submenu->processShortcutKey(km);
			}
		}
		return sl_false;
	}
	
	
	MenuItemParam::MenuItemParam()
	{
		flagEnabled = sl_true;
		flagChecked = sl_false;
	}
	
	MenuItemParam::~MenuItemParam()
	{
	}

	SLIB_DEFINE_OBJECT(Menu, Object)
	
	Menu::Menu()
	{
	}
	
	Menu::~Menu()
	{
	}

	sl_uint32 Menu::getMenuItemsCount() const
	{
		return (sl_uint32)(m_items.getCount());
	}
	
	Ref<MenuItem> Menu::getMenuItem(sl_uint32 index) const
	{
		return m_items.getValueAt(index);
	}
	
	void Menu::show(const UIPoint& pt)
	{
		show(pt.x, pt.y);
	}
	
	Ref<MenuItem> Menu::addMenuItem(const String& title)
	{
		MenuItemParam param;
		param.text = title;
		return addMenuItem(param);
	}
	
	Ref<MenuItem> Menu::addMenuItem(const String& title, const Ref<Bitmap>& icon)
	{
		MenuItemParam param;
		param.text = title;
		param.icon = icon;
		return addMenuItem(param);
	}
	
	Ref<MenuItem> Menu::addMenuItem(const String& title, const Ref<Bitmap>& icon, const Ref<Bitmap>& checkedIcon)
	{
		MenuItemParam param;
		param.text = title;
		param.icon = icon;
		param.checkedIcon = checkedIcon;
		return addMenuItem(param);
	}
	
	Ref<MenuItem> Menu::addMenuItem(const String& title, const KeycodeAndModifiers& shortcutKey)
	{
		MenuItemParam param;
		param.text = title;
		param.shortcutKey = shortcutKey;
		return addMenuItem(param);
	}
	
	Ref<MenuItem> Menu::addMenuItem(const String& title, const KeycodeAndModifiers& shortcutKey, const Ref<Bitmap>& icon)
	{
		MenuItemParam param;
		param.text = title;
		param.shortcutKey = shortcutKey;
		param.icon = icon;
		return addMenuItem(param);
	}
	
	Ref<MenuItem> Menu::addMenuItem(const String& title, const KeycodeAndModifiers& shortcutKey, const Ref<Bitmap>& icon, const Ref<Bitmap>& checkedIcon)
	{
		MenuItemParam param;
		param.text = title;
		param.shortcutKey = shortcutKey;
		param.icon = icon;
		param.checkedIcon = checkedIcon;
		return addMenuItem(param);
	}
	
	Ref<MenuItem> Menu::addSubmenu(Ref<Menu>& submenu, const String& title)
	{
		MenuItemParam param;
		param.text = title;
		param.submenu = submenu;
		return addMenuItem(param);
	}
	
	Ref<MenuItem> Menu::addSubmenu(Ref<Menu>& submenu, const String& title, const Ref<Bitmap>& icon)
	{
		MenuItemParam param;
		param.text = title;
		param.icon = icon;
		param.submenu = submenu;
		return addMenuItem(param);
	}
	
	Ref<MenuItem> Menu::addSubmenu(Ref<Menu>& submenu, const String& title, const Ref<Bitmap>& icon, const Ref<Bitmap>& checkedIcon)
	{
		MenuItemParam param;
		param.text = title;
		param.icon = icon;
		param.checkedIcon = checkedIcon;
		param.submenu = submenu;
		return addMenuItem(param);
	}
	
	sl_bool Menu::processShortcutKey(const KeycodeAndModifiers& km)
	{
		if (km != 0) {
			ListLocker< Ref<MenuItem> > items(m_items);
			for (sl_size i = 0; i < items.count; i++) {
				Ref<MenuItem>& item = items[i];
				if (item.isNotNull()) {
					if (item->processShortcutKey(km)) {
						return sl_true;
					}
				}
			}
		}
		return sl_false;
	}
	
	
#if !defined(SLIB_UI_IS_MACOS) && !defined(SLIB_UI_IS_WIN32)
	
	Ref<Menu> Menu::create()
	{
		return sl_null;
	}
	
#endif
}
