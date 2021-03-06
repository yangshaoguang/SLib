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

#include "slib/core/definition.h"

#if defined(SLIB_UI_IS_MACOS)

#include "slib/ui/select_view.h"

#include "view_macos.h"

@interface _priv_Slib_macOS_SelectView : NSPopUpButton {
	
	@public slib::WeakRef<slib::macOS_ViewInstance> m_viewInstance;

}

@end

namespace slib
{

	class _priv_SelectView : public SelectView
	{
	public:
		void _applyItemsCount(NSPopUpButton* v)
		{
			ObjectLocker lock(this);
			sl_uint32 nOrig = (sl_uint32)([v numberOfItems]);
			sl_uint32 nNew = (sl_uint32)(m_titles.getCount());
			if (nOrig == nNew) {
				return;
			}
			if (nOrig > nNew) {
				if (nNew  > 0) {
					for (sl_uint32 i = nOrig; i > nNew; i--) {
						[v removeItemAtIndex:(i - 1)];
					}
				} else {
					[v removeAllItems];
				}
			} else {
				for (sl_uint32 i = nOrig; i < nNew; i++) {
					[v addItemWithTitle:[NSString stringWithFormat:@"%d",i]];
					NSMenuItem* item = [v lastItem];
					if (item != nil) {
						NSString* s = Apple::getNSStringFromString(m_titles.getValueAt(i));
						if (s == nil) {
							s = @"";
						}
						[item setTitle:s];
					}
				}
			}
		}
		
		void _copyItems(NSPopUpButton* v)
		{
			[v removeAllItems];
			_applyItemsCount(v);
			if (m_indexSelected >= m_titles.getCount()) {
				m_indexSelected = 0;
			}
			if ([v numberOfItems] > 0) {
				[v selectItemAtIndex:m_indexSelected];
			}
		}
		
		void _setItemTitle(NSPopUpButton* v, sl_uint32 index, const String& title)
		{
			NSString* s = Apple::getNSStringFromString(title);
			if (s == nil) {
				s = @"";
			}
			NSMenuItem* item = [v itemAtIndex:index];
			if (item != nil) {
				[item setTitle:s];
			}
		}
		
		sl_uint32 _getSelectedIndex(NSPopUpButton* v)
		{
			return (sl_uint32)([v indexOfSelectedItem]);
		}
		
		void _onSelectItem(NSPopUpButton* v)
		{
			dispatchSelectItem(_getSelectedIndex(v));
		}
	};

	Ref<ViewInstance> SelectView::createNativeWidget(ViewInstance* _parent)
	{
		MACOS_VIEW_CREATE_INSTANCE_BEGIN
		_priv_Slib_macOS_SelectView* handle = [[_priv_Slib_macOS_SelectView alloc] initWithFrame:frame];
		if (handle != nil) {
			[handle setPullsDown:NO];
			((_priv_SelectView*)this)->_copyItems(handle);
			
			Ref<Font> font = getFont();
			NSFont* hFont = GraphicsPlatform::getNSFont(font.get());
			if (hFont != nil) {
				[handle setFont:hFont];
			}
		}
		MACOS_VIEW_CREATE_INSTANCE_END
		return ret;
	}

	void SelectView::_getSelectedIndex_NW()
	{
		NSView* handle = UIPlatform::getViewHandle(this);
		if (handle != nil && [handle isKindOfClass:[NSPopUpButton class]]) {
			NSPopUpButton* v = (NSPopUpButton*)handle;
			m_indexSelected = ((_priv_SelectView*)this)->_getSelectedIndex(v);
		}
	}

	void SelectView::_select_NW(sl_uint32 index)
	{
		NSView* handle = UIPlatform::getViewHandle(this);
		if (handle != nil && [handle isKindOfClass:[NSPopUpButton class]]) {
			NSPopUpButton* v = (NSPopUpButton*)handle;
			[v selectItemAtIndex:index];
		}
	}

	void SelectView::_refreshItemsCount_NW()
	{
		NSView* handle = UIPlatform::getViewHandle(this);
		if (handle != nil && [handle isKindOfClass:[NSPopUpButton class]]) {
			NSPopUpButton* v = (NSPopUpButton*)handle;
			((_priv_SelectView*)this)->_applyItemsCount(v);
		}
	}

	void SelectView::_refreshItemsContent_NW()
	{
		NSView* handle = UIPlatform::getViewHandle(this);
		if (handle != nil && [handle isKindOfClass:[NSPopUpButton class]]) {
			NSPopUpButton* v = (NSPopUpButton*)handle;
			((_priv_SelectView*)this)->_copyItems(v);
		}
	}

	void SelectView::_setItemTitle_NW(sl_uint32 index, const String& title)
	{
		NSView* handle = UIPlatform::getViewHandle(this);
		if (handle != nil && [handle isKindOfClass:[NSPopUpButton class]]) {
			NSPopUpButton* v = (NSPopUpButton*)handle;
			((_priv_SelectView*)this)->_setItemTitle(v, index, title);
		}
	}

	void SelectView::_setFont_NW(const Ref<Font>& font)
	{
		NSView* handle = UIPlatform::getViewHandle(this);
		if (handle != nil && [handle isKindOfClass:[NSPopUpButton class]]) {
			NSPopUpButton* v = (NSPopUpButton*)handle;
			NSFont* hFont = GraphicsPlatform::getNSFont(font.get());
			if (hFont != nil) {
				[v setFont:hFont];
			}
		}
	}

}

@implementation _priv_Slib_macOS_SelectView
-(id)initWithFrame:(NSRect)frame
{
	self = [super initWithFrame:frame];
	if (self != nil) {
		[self setAction: @selector(onSelect)];
		[self setTarget:self];
	}
	return self;
}

-(void)onSelect
{
	slib::Ref<slib::macOS_ViewInstance> instance = m_viewInstance;
	if (instance.isNotNull()) {
		slib::Ref<slib::View> view = instance->getView();
		if (slib::_priv_SelectView* _view = slib::CastInstance<slib::_priv_SelectView>(view.get())) {
			_view->_onSelectItem(self);
		}
	}
}
@end

#endif
