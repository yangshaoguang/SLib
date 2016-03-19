#include "../../../inc/slib/ui/radio_group.h"

#include "../../../inc/slib/ui/radio_button.h"
#include "../../../inc/slib/ui/check_box.h"
#include "../../../inc/slib/ui/s_check_box.h"

SLIB_UI_NAMESPACE_BEGIN

SLIB_DEFINE_OBJECT(RadioGroup, Object)

RadioGroup::RadioGroup()
{
}

void RadioGroup::addView(const Ref<View>& view)
{
	if (view.isNotNull()) {
		if (RadioButton::checkInstance(view.ptr)) {
			((RadioButton*)(view.ptr))->setRadioGroup(this);
		} else if (CheckBox::checkInstance(view.ptr)) {
			((CheckBox*)(view.ptr))->setRadioGroup(this);
		} else if (SCheckBox::checkInstance(view.ptr)) {
			((SCheckBox*)(view.ptr))->setRadioGroup(this);
		} else {
			return;
		}
		m_views.addIfNotExist(view);
		select(m_viewSelected);
	}
}

void RadioGroup::removeView(const Ref<View>& view)
{
	m_views.removeValue(view);
}

void RadioGroup::select(const Ref<View>& sel)
{
	m_viewSelected = sel;
	ListLocker< Ref<View> > views(m_views);
	for (sl_size i = 0; i < views.count; i++) {
		Ref<View> view = views[i];
		if (view.isNotNull() && view != sel) {
			_setChecked(view.ptr, sl_false);
		}
	}
	if (sel.isNotNull()) {
		_setChecked(sel.ptr, sl_true);
	}
}

Ref<View> RadioGroup::getSelectedView()
{
	return m_viewSelected;
}

void RadioGroup::_setChecked(View* view, sl_bool flag)
{
	if (RadioButton::checkInstance(view)) {
		((RadioButton*)(view))->setChecked(flag);
	} else if (CheckBox::checkInstance(view)) {
		((CheckBox*)(view))->setChecked(flag);
	} else if (SCheckBox::checkInstance(view)) {
		((SCheckBox*)(view))->setChecked(flag);
	}
}

SLIB_UI_NAMESPACE_END
