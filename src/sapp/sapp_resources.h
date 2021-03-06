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

#ifndef CHECKHEADER_SLIB_SDEV_SAPP_RESOURCES
#define CHECKHEADER_SLIB_SDEV_SAPP_RESOURCES

#include "sapp_values.h"

#include "slib/core/locale.h"
#include "slib/core/xml.h"
#include "slib/graphics/image.h"
#include "slib/ui/event.h"
#include "slib/ui/resource.h"

namespace slib
{

	class SAppStringResource : public Referable
	{
	public:
		String name;
		String defaultValue;
		CHashMap<Locale, String> values;
	};
	
	class SAppColorResource : public Referable
	{
	public:
		String name;
		Color value;
	};

	class SAppRawResource : public Referable
	{
	public:
		String name;
		String filePath;
	};

	class SAppDrawableResourceImageItem : public Object
	{
	public:
		String fileName;
		String filePath;
		String rawName;
		AtomicRef<Image> image;
		
	public:
		Ref<Image> loadImage();
		
	};

	class SAppDrawableResourceImageAttributes : public Referable
	{
	public:
		List< Ref<SAppDrawableResourceImageItem> > defaultImages;
		CHashMap< Locale, List< Ref<SAppDrawableResourceImageItem> > > images;

	public:
		SAppDrawableResourceImageAttributes();
		
	};

	class SAppDrawableResourceNinePiecesAttributes : public Referable
	{
	public:
		Ref<XmlElement> element;
		
		String localNamespace;
		
		SAppDimensionValue leftWidth;
		SAppDimensionValue rightWidth;
		SAppDimensionValue topHeight;
		SAppDimensionValue bottomHeight;
		
		SAppDrawableValue topLeft;
		SAppDrawableValue top;
		SAppDrawableValue topRight;
		SAppDrawableValue left;
		SAppDrawableValue center;
		SAppDrawableValue right;
		SAppDrawableValue bottomLeft;
		SAppDrawableValue bottom;
		SAppDrawableValue bottomRight;
		
	};

	class SAppDrawableResourceNinePatchAttributes : public Referable
	{
	public:
		Ref<XmlElement> element;
		
		String localNamespace;
		
		SAppDimensionValue dstLeftWidth;
		SAppDimensionValue dstRightWidth;
		SAppDimensionValue dstTopHeight;
		SAppDimensionValue dstBottomHeight;
		
		SAppDrawableValue src;
		sl_real leftWidth;
		sl_real rightWidth;
		sl_real topHeight;
		sl_real bottomHeight;
		
	};

	class SAppDrawableResource : public Referable
	{
	public:
		String name;
		int type;
		enum {
			typeUnknown = 0,
			typeImage = 1,
			typeNinePieces = 2,
			typeNinePatch = 3
		};
		
		Ref<SAppDrawableResourceImageAttributes> imageAttrs;
		Ref<SAppDrawableResourceNinePiecesAttributes> ninePiecesAttrs;
		Ref<SAppDrawableResourceNinePatchAttributes> ninePatchAttrs;
		
	public:
		SAppDrawableResource();
		
	};


	class SAppMenuResourceItem : public Referable
	{
	public:
		Ref<XmlElement> element;
		String name;
		int type;
		enum {
			typeSubmenu = 0,
			typeItem = 1,
			typeSeparator = 2
		};
		int platformFlags;
		enum {
			mac = 1,
			windows = 2,
			linux = 4,
			all_platforms = 0xFFFF,
			no_mac = 0xFFFE,
			no_windows = 0xFFFD,
			no_linux = 0xFFFB
		};
		SAppStringValue title;
		KeycodeAndModifiers shortcutKey;
		KeycodeAndModifiers macShortcutKey;
		SAppDrawableValue icon;
		SAppDrawableValue checkedIcon;
		CList< Ref<SAppMenuResourceItem> > children;
	};

	class SAppMenuResource : public Referable
	{
	public:
		String name;
		String localNamespace;
		CList< Ref<SAppMenuResourceItem> > children;
		CHashMap<String, Ref<SAppMenuResourceItem> > itemsWindows;
		CHashMap<String, Ref<SAppMenuResourceItem> > itemsLinux;
		CHashMap<String, Ref<SAppMenuResourceItem> > itemsMac;
	};


	class SAppLayoutResourceItem;

	class SAppLayoutWindowAttributes : public Referable
	{
	public:
		SAppMenuValue menu;
		SAppStringValue title;
		
		SAppDimensionValue left;
		SAppDimensionValue top;
		SAppDimensionValue width;
		SAppDimensionValue height;
		
		SAppDimensionValue minWidth;
		SAppDimensionValue maxWidth;
		SAppDimensionValue minHeight;
		SAppDimensionValue maxHeight;
		SAppFloatValue minAspectRatio;
		SAppFloatValue maxAspectRatio;
		SAppFloatValue aspectRatio;

		SAppBooleanValue minimized;
		SAppBooleanValue maximized;
		SAppBooleanValue visible;
		SAppBooleanValue alwaysOnTop;
		SAppBooleanValue closeButton;
		SAppBooleanValue minimizeButton;
		SAppBooleanValue maximizeButton;
		SAppBooleanValue resizable;
		SAppFloatValue alpha;
		SAppBooleanValue transparent;
		
		SAppBooleanValue modal;
		SAppBooleanValue dialog;
		SAppBooleanValue borderless;
		SAppBooleanValue titleBar;
		SAppBooleanValue fullScreen;
		SAppBooleanValue centerScreen;
	};

	class SAppLayoutViewAttributes : public Referable
	{
	public:
		SAppStringValue id;
		
		SAppDimensionValue width;
		SAppDimensionValue height;

		PositionMode leftMode;
		PositionMode topMode;
		PositionMode rightMode;
		PositionMode bottomMode;
		String leftReferingView;
		String topReferingView;
		String rightReferingView;
		String bottomReferingView;
		
		SAppDimensionValue left;
		SAppDimensionValue top;
		
		SAppDimensionValue minWidth;
		SAppDimensionValue maxWidth;
		SAppDimensionValue minHeight;
		SAppDimensionValue maxHeight;
		
		SAppFloatValue aspectRatio;

		SAppDimensionValue marginLeft;
		SAppDimensionValue marginTop;
		SAppDimensionValue marginRight;
		SAppDimensionValue marginBottom;

		SAppDimensionValue paddingLeft;
		SAppDimensionValue paddingTop;
		SAppDimensionValue paddingRight;
		SAppDimensionValue paddingBottom;
		
		SAppVisibilityValue visibility;
		SAppBooleanValue visible;
		SAppBooleanValue enabled;
		SAppBooleanValue clipping;
		SAppBooleanValue drawing;
		
		SAppDrawableValue background;
		SAppDrawableValue pressedBackground;
		SAppDrawableValue hoverBackground;
		SAppScaleModeValue backgroundScale;
		SAppAlignmentValue backgroundAlign;
		SAppBooleanValue border;
		SAppDimensionFloatValue borderWidth;
		SAppColorValue borderColor;
		SAppPenStyleValue borderStyle;
		SAppBoundShapeValue boundShape;
		SAppDimensionFloatValue boundRadiusX;
		SAppDimensionFloatValue boundRadiusY;
		SAppDimensionValue boundRadius;
		
		SAppStringValue fontFamily;
		SAppDimensionFloatValue fontSize;
		SAppBooleanValue fontBold;
		SAppBooleanValue fontItalic;
		SAppBooleanValue fontUnderline;
		SAppStringValue finalFontFamily;
		SAppDimensionFloatValue finalFontSize;
		sl_bool finalFontBold;
		sl_bool finalFontItalic;
		sl_bool finalFontUnderline;
		
		SAppBooleanValue opaque;
		SAppFloatValue alpha;
		SAppBooleanValue layer;
		
		SAppScrollingValue scrolling;
		SAppScrollBarsValue scrollBars;
		SAppBooleanValue paging;
		SAppDimensionValue pageWidth;
		SAppDimensionValue pageHeight;
		SAppBooleanValue scrollingByMouse;
		SAppBooleanValue scrollingByTouch;
		SAppBooleanValue scrollingByMouseWheel;
		SAppBooleanValue scrollingByKeyboard;
		
		SAppBooleanValue touchMultipleChildren;
		SAppBooleanValue tabStop;

		SAppBooleanValue instance;
		SAppBooleanValue childInstances;
		SAppBooleanValue nativeWidget;
		SAppBooleanValue hardwareLayer;
		
	public:
		SAppLayoutViewAttributes();
		
		sl_bool isNotRequiredNative(sl_bool flagCheckBackgroundColor);

	};

	class SAppLayoutImportAttributes : public Referable
	{
	public:
		String layout;
		
	};

	class SAppLayoutButtonCategory
	{
	public:
		SAppColorValue textColor[(int)(ButtonState::Count)];
		SAppDrawableValue background[(int)(ButtonState::Count)];
		SAppDrawableValue icon[(int)(ButtonState::Count)];
		SAppDimensionFloatValue borderWidth[(int)(ButtonState::Count)];
		SAppColorValue borderColor[(int)(ButtonState::Count)];
		SAppPenStyleValue borderStyle[(int)(ButtonState::Count)];
		
	};

	#define SLIB_SAPP_LAYOUT_BUTTON_CATEGORY_MAX 4

	class SAppLayoutButtonAttributes : public Referable
	{
	public:
		SAppStringValue text;
		SAppBooleanValue multiLine;
		SAppBooleanValue defaultButton;
		SAppColorValue textColor;
		SAppDrawableValue icon;
		SAppDimensionValue iconWidth;
		SAppDimensionValue iconHeight;
		SAppAlignmentValue gravity;
		SAppAlignmentValue iconAlign;
		SAppAlignmentValue textAlign;
		SAppBooleanValue textBeforeIcon;
		SAppLayoutOrientationValue orientation;
		SAppDimensionValue iconMarginLeft;
		SAppDimensionValue iconMarginTop;
		SAppDimensionValue iconMarginRight;
		SAppDimensionValue iconMarginBottom;
		SAppDimensionValue textMarginLeft;
		SAppDimensionValue textMarginTop;
		SAppDimensionValue textMarginRight;
		SAppDimensionValue textMarginBottom;
		SAppBooleanValue defaultColorFilter;
		
		SAppLayoutButtonCategory categories[SLIB_SAPP_LAYOUT_BUTTON_CATEGORY_MAX];
		
	public:
		sl_bool isNotRequiredNative();
		
	};

	class SAppLayoutLabelAttributes : public Referable
	{
	public:
		SAppStringValue text;
		SAppColorValue textColor;
		SAppAlignmentValue gravity;
		SAppMultiLineModeValue multiLine;
		
	public:
		sl_bool isNotRequiredNative();

	};

	class SAppLayoutCheckAttributes : public Referable
	{
	public:
		SAppBooleanValue checked;
		
	};

	class SAppLayoutRadioAttributes : public Referable
	{
	public:
		String group;
		
	};

	class SAppLayoutEditAttributes : public Referable
	{
	public:
		SAppStringValue text;
		SAppAlignmentValue gravity;
		SAppStringValue hintText;
		SAppBooleanValue readOnly;
		SAppBooleanValue multiLine;
		SAppColorValue textColor;
		SAppColorValue hintTextColor;
		SAppUIReturnKeyTypeValue returnKey;
		SAppUIKeyboardTypeValue keyboard;
		SAppUIAutoCapitalizationType autoCap;
		
	public:
		sl_bool isNotRequiredNative();

	};

	class SAppLayoutImageAttributes : public Referable
	{
	public:
		SAppDrawableValue src;
		SAppScaleModeValue scale;
		SAppAlignmentValue gravity;
		
	};

	class SAppLayoutSelectItem
	{
	public:
		SAppStringValue title;
		SAppStringValue value;
		SAppBooleanValue selected;
		
		Ref<XmlElement> element;
	};

	class SAppLayoutSelectAttributes : public Referable
	{
	public:
		SAppDimensionValue iconWidth;
		SAppDimensionValue iconHeight;
		SAppDrawableValue leftIcon;
		SAppDrawableValue rightIcon;
		SAppColorValue textColor;
		SAppAlignmentValue gravity;
		
		CList<SAppLayoutSelectItem> items;
		
	public:
		sl_bool isNotRequiredNative();
		
	};

	class SAppLayoutScrollAttributes : public Referable
	{
	public:
		Ref<SAppLayoutResourceItem> content;
		
	};

	class SAppLayoutLinearAttributes : public Referable
	{
	public:
		SAppLayoutOrientationValue orientation;
		
	};

	class SAppLayoutListAttributes : public Referable
	{
	public:
		String itemLayout;
		
	};

	struct SAppLayoutListReportColumn
	{
		SAppStringValue title;
		SAppDimensionValue width;
		SAppAlignmentValue align;
		SAppAlignmentValue headerAlign;
	};

	class SAppLayoutListReportAttributes : public Referable
	{
	public:
		CList<SAppLayoutListReportColumn> columns;
		
	};

	class SAppLayoutRenderAttributes : public Referable
	{
	public:
		SAppRedrawModeValue redraw;
		
	};

	struct SAppLayoutTabItem
	{
		SAppStringValue label;
		SAppBooleanValue selected;
		Ref<SAppLayoutResourceItem> view;
		
		Ref<XmlElement> element;
		
	};

	class SAppLayoutTabAttributes : public Referable
	{
	public:
		SAppLayoutOrientationValue orientation;
		SAppDimensionValue tabWidth;
		SAppDimensionValue tabHeight;
		SAppDrawableValue barBackground;
		SAppDrawableValue contentBackground;
		SAppDrawableValue tabBackground;
		SAppDrawableValue selectedTabBackground;
		SAppDrawableValue hoverTabBackground;
		SAppColorValue labelColor;
		SAppColorValue selectedLabelColor;
		SAppColorValue hoverLabelColor;
		SAppAlignmentValue labelAlign;
		SAppDimensionValue labelMarginLeft;
		SAppDimensionValue labelMarginTop;
		SAppDimensionValue labelMarginRight;
		SAppDimensionValue labelMarginBottom;
		
		CList<SAppLayoutTabItem> items;
		
	public:
		sl_bool isNotRequiredNative();
		
	};


	struct SAppLayoutTreeItem
	{
		String name;
		SAppStringValue id;
		SAppStringValue text;
		SAppDrawableValue icon;
		SAppDrawableValue opendIcon;
		SAppDrawableValue closedIcon;
		SAppColorValue textColor;
		SAppColorValue hoverTextColor;
		SAppColorValue selectedTextColor;
		SAppDimensionValue height;
		
		Ref<SAppLayoutResourceItem> customView;
		Ref<XmlElement> element;
	};

	class SAppLayoutTreeAttributes : public Referable
	{
	public:
		SAppDrawableValue itemIcon;
		SAppDrawableValue opendIcon;
		SAppDrawableValue closedIcon;
		SAppDrawableValue collapsedIcon;
		SAppDrawableValue expandedIcon;
		SAppColorValue selectedBackgroundColor;
		SAppColorValue textColor;
		SAppColorValue hoverTextColor;
		SAppColorValue selectedTextColor;
		SAppDimensionValue itemHeight;
		SAppDimensionValue itemPadding;
		SAppDimensionValue itemIndent;
		SAppDimensionValue textIndent;

	};

	struct SAppLayoutSplitItem
	{
		Ref<SAppLayoutResourceItem> view;
		SAppFloatValue weight;
		SAppFloatValue minWeight;
		SAppFloatValue maxWeight;
		SAppDimensionValue minSize;
		SAppDimensionValue maxSize;
		SAppDimensionValue dividerWidth;
		SAppDrawableValue dividerBackground;
		SAppColorValue dividerColor;
		
		Ref<XmlElement> element;
		
	};

	class SAppLayoutSplitAttributes : public Referable
	{
	public:
		SAppLayoutOrientationValue orientation;
		SAppDimensionValue dividerWidth;
		SAppDrawableValue dividerBackground;
		SAppColorValue dividerColor;
		SAppDimensionValue cursorMargin;
		
		CList<SAppLayoutSplitItem> items;
		
	};

	class SAppLayoutWebAttributes : public Referable
	{
	public:
		SAppStringValue url;
		SAppStringValue html;
		
	};

	class SAppLayoutProgressAttributes : public Referable
	{
	public:
		SAppLayoutOrientationValue orientation;
		SAppFloatValue min;
		SAppFloatValue max;
		SAppFloatValue range;
		SAppFloatValue value;
		SAppFloatValue value2;
		SAppBooleanValue dual;
		SAppBooleanValue discrete;
		SAppFloatValue step;
		SAppBooleanValue reversed;
		SAppDrawableValue track;
		SAppDrawableValue progress;
		SAppDrawableValue progress2;
		
	};

	class SAppLayoutSliderAttributes : public Referable
	{
	public:
		SAppDrawableValue thumb;
		SAppDrawableValue pressedThumb;
		SAppDrawableValue hoverThumb;
		SAppDimensionValue thumbWidth;
		SAppDimensionValue thumbHeight;
		
	};

	class SAppLayoutPickerAttributes : public Referable
	{
	public:
		SAppColorValue textColor;
		
		CList<SAppLayoutSelectItem> items;
		
	public:
		sl_bool isNotRequiredNative();
		
	};

	struct SAppLayoutPagerItem
	{
		SAppBooleanValue selected;
		Ref<SAppLayoutResourceItem> view;
		
		Ref<XmlElement> element;
		
	};

	class SAppLayoutPagerAttributes : public Referable
	{
	public:
		SAppBooleanValue swipe;
		
		CList<SAppLayoutPagerItem> items;
		
	};

	class SAppLayoutVideoAttributes : public Referable
	{
	public:
		SAppStringValue src;
		SAppBooleanValue repeat;
		
	};


	class SAppLayoutStyle : public Referable
	{
	public:
		Ref<XmlElement> element;
		String name;
	};

	class SAppLayoutInclude : public Referable
	{
	public:
		Ref<XmlElement> element;
		String name;
	};

	enum class SAppLayoutType
	{
		Window = 0,
		Page = 1,
		View = 2
	};

	enum class SAppLayoutItemType
	{
		Unknown = 0,
		
		View = 0x0200,
		ViewGroup = 0x0201,
		Import = 0x0202,
		
		Button = 0x0210,
		Label = 0x0211,
		Check = 0x0212,
		Radio = 0x0213,
		Edit = 0x0214,
		Password = 0x0215,
		TextArea = 0x0216,
		Image = 0x0217,
		Select = 0x0218,
		
		Scroll = 0x0230,
		Linear = 0x0231,
		List = 0x0232,
		ListReport = 0x0233,
		Render = 0x0234,
		Tab = 0x0235,
		Tree = 0x0236,
		Web = 0x0237,
		Split = 0x0238,
		
		Progress = 0x0240,
		Slider = 0x0241,
		Picker = 0x0242,
		Pager = 0x0243,
		Video = 0x0244
	};

	class SAppLayoutResourceItem : public Referable
	{
	public:
		Ref<XmlElement> element;
		
		SAppLayoutItemType itemType;
		String name;
		sl_bool flagGeneratedName;
		
		String className;
		
		Ref<SAppLayoutWindowAttributes> attrsWindow;
		Ref<SAppLayoutViewAttributes> attrsView;
		Ref<SAppLayoutImportAttributes> attrsImport;
		Ref<SAppLayoutButtonAttributes> attrsButton;
		Ref<SAppLayoutLabelAttributes> attrsLabel;
		Ref<SAppLayoutCheckAttributes> attrsCheck;
		Ref<SAppLayoutRadioAttributes> attrsRadio;
		Ref<SAppLayoutEditAttributes> attrsEdit;
		Ref<SAppLayoutImageAttributes> attrsImage;
		Ref<SAppLayoutSelectAttributes> attrsSelect;
		Ref<SAppLayoutScrollAttributes> attrsScroll;
		Ref<SAppLayoutLinearAttributes> attrsLinear;
		Ref<SAppLayoutListAttributes> attrsList;
		Ref<SAppLayoutListReportAttributes> attrsListReport;
		Ref<SAppLayoutRenderAttributes> attrsRender;
		Ref<SAppLayoutTabAttributes> attrsTab;
		Ref<SAppLayoutTreeAttributes> attrsTree;
		Ref<SAppLayoutSplitAttributes> attrsSplit;
		Ref<SAppLayoutWebAttributes> attrsWeb;
		Ref<SAppLayoutProgressAttributes> attrsProgress;
		Ref<SAppLayoutSliderAttributes> attrsSlider;
		Ref<SAppLayoutPickerAttributes> attrsPicker;
		Ref<SAppLayoutPagerAttributes> attrsPager;
		Ref<SAppLayoutVideoAttributes> attrsVideo;

		CList< Ref<SAppLayoutStyle> > styles;
		CList< Ref<SAppLayoutResourceItem> > children;
		
	public:
		SAppLayoutResourceItem();
		
	public:
		String getXmlAttribute(const String& name);
		
	};

	class SAppLayoutResource : public SAppLayoutResourceItem
	{
	public:
		SAppLayoutType layoutType;
		
		SAppDimensionFloatValue sp;
		
		CHashMap< String, Ref<SAppLayoutResourceItem> > itemsByName;
		CMap<String, sl_bool> customClasses;
		CMap<String, sl_bool> radioGroups;

		sl_uint32 nAutoIncreaseNameView;
		sl_uint32 nAutoIncreaseNameViewGroup;
		sl_uint32 nAutoIncreaseNameImport;
		sl_uint32 nAutoIncreaseNameButton;
		sl_uint32 nAutoIncreaseNameLabel;
		sl_uint32 nAutoIncreaseNameCheck;
		sl_uint32 nAutoIncreaseNameRadio;
		sl_uint32 nAutoIncreaseNameEdit;
		sl_uint32 nAutoIncreaseNamePassword;
		sl_uint32 nAutoIncreaseNameTextArea;
		sl_uint32 nAutoIncreaseNameImage;
		sl_uint32 nAutoIncreaseNameSelect;
		sl_uint32 nAutoIncreaseNameScroll;
		sl_uint32 nAutoIncreaseNameLinear;
		sl_uint32 nAutoIncreaseNameList;
		sl_uint32 nAutoIncreaseNameListReport;
		sl_uint32 nAutoIncreaseNameRender;
		sl_uint32 nAutoIncreaseNameTab;
		sl_uint32 nAutoIncreaseNameTree;
		sl_uint32 nAutoIncreaseNameWeb;
		sl_uint32 nAutoIncreaseNameSplit;
		sl_uint32 nAutoIncreaseNameProgress;
		sl_uint32 nAutoIncreaseNameSlider;
		sl_uint32 nAutoIncreaseNamePicker;
		sl_uint32 nAutoIncreaseNamePager;
		sl_uint32 nAutoIncreaseNameVideo;
		
	public:
		SAppLayoutResource();
		
	public:
		String getAutoIncreasingName(SAppLayoutItemType type);
		
		static SAppLayoutItemType getTypeFromName(const String& strType);
		
	};
	
	
	class SAppLayoutSimulationParams
	{
	public:
		sl_ui_len screenWidth;
		sl_ui_len screenHeight;
		sl_ui_len viewportWidth;
		sl_ui_len viewportHeight;
		sl_real sp;
		
	public:
		SAppLayoutSimulationParams();
		
	};

	class SAppDocument;
	class SAppLayoutSimulationWindow;

	class SAppLayoutSimulator
	{
	public:
		Ref<Referable> getReferable();
		
		Ref<View> getViewByName(const String& name);
		
		void registerViewByName(const String& name, const Ref<View>& view);
		
		Ref<RadioGroup> getRadioGroup(const String& name);
		
		Ref<SAppDocument> getDocument();
		
		Ref<SAppLayoutResource> getLayoutResource();
		
		Ref<SAppLayoutSimulationWindow> getSimulationWindow();
		
		Ref<View> getSimulationContentView();
		
	protected:
		AtomicWeakRef<Referable> m_refer;
		AtomicWeakRef<SAppDocument> m_document;
		AtomicRef<SAppLayoutResource> m_layoutResource;
		AtomicWeakRef<SAppLayoutSimulationWindow> m_simulationWindow;
		AtomicWeakRef<View> m_simulationContentView;
		CHashMap< String, Ref<View> > m_views;
		CHashMap< String, Ref<RadioGroup> > m_radioGroups;

	};

	class SAppLayoutSimulationWindow : public WindowLayoutResource, public SAppLayoutSimulator
	{
	public:
		SAppLayoutSimulationWindow();
		
	public:
		void open(SAppDocument* doc, SAppLayoutResource* layout);
		
	protected:
		// override
		void layoutViews(sl_ui_len width, sl_ui_len height);
		
		// override
		void onClose(UIEvent* ev);
		
	};

	class SAppLayoutImportView : public ViewLayoutResource, public SAppLayoutSimulator
	{
	public:
		SAppLayoutImportView();
		
	public:
		void init(SAppLayoutSimulator* simulator, SAppLayoutResource* layout);
		
		// override
		void layoutViews(sl_ui_len width, sl_ui_len height);
		
	};

}

#endif
