#include "editfield.hpp"

#pragma warning(push, 0)  
#include <boost/assign/list_of.hpp>
#pragma warning(pop)

// ISO-LEVEL 2 

EditField::EditField(SDL_Object* const edit_parent, 
						   const Rect& edit_rect, 
						   const Size& edit_size, 
						   const boost::shared_ptr<const Font>& st_font, 
						   const boost::shared_ptr<const Color>& text_color,
						   const boost::shared_ptr<const ButtonColors>& button_colors,
						   const boost::shared_ptr<const Text>& formatText,
						   const ePositionMode position_mode, 
						   const boost::shared_ptr<const Text>& description_text, 
						   const std::string& initialText) :
	Object(edit_parent, edit_rect, edit_size, position_mode),
	position(initialText.size()),
	ani(5),
	pressedEnter(false),
	pressedEscape(false),
	editField(new Button(this, Rect(Point(120, 0), Size(200, st_font->getTextExtent("01gfFA").getHeight()+8)), Size(0,0), button_colors, formatText, boost::shared_ptr<const Text>(), boost::assign::list_of(text), boost::shared_ptr<const Bitmap>(), TAB_BUTTON_MODE, SPECIAL_BUTTON_LEFT)),
	descriptionText(new StaticText(this, Rect(Point(0, 4), Size(100, st_font->getTextExtent("01gfFA").getHeight()+8)), Size(0,0), text_color, st_font, description_text, std::list<std::string>(), DO_NOT_ADJUST)),
	text(initialText)
{ }


void EditField::resetData()
{
	text = "";
	editField->updateParameters(boost::assign::list_of(text));
	
	pressedEnter = false;
	pressedEscape = false;
}

EditField::~EditField()
{
	delete editField;
	delete descriptionText;
}



bool EditField::addKey(unsigned int key, unsigned int mod)
{
	switch(key)
	{
		case SDLK_KP_ENTER:
		case SDLK_RETURN:
			if((text.length()>0) && (!(mod & (KMOD_LALT | KMOD_RALT | KMOD_ALT)))) {
				enterWasPressed();break;
			}
		case SDLK_ESCAPE:escapeWasPressed();break;
		case SDLK_SPACE:addChar(' ');break;
		case SDLK_UNDERSCORE:addChar('_');break;
		case SDLK_DELETE:removeCharDelete();break;
		case SDLK_BACKSPACE:removeCharBackspace();break;
		case SDLK_KP0:
		case SDLK_KP1:
		case SDLK_KP2:
		case SDLK_KP3:
		case SDLK_KP4:
		case SDLK_KP5:
		case SDLK_KP6:
		case SDLK_KP7:
		case SDLK_KP8:
		case SDLK_KP9:addChar('0'+key-SDLK_0);break;
		case SDLK_MINUS:if(mod & (KMOD_LSHIFT | KMOD_RSHIFT)) addChar('_'); else return false;break;
		case SDLK_a:
		case SDLK_b:
		case SDLK_c:
		case SDLK_d:
		case SDLK_e:
		case SDLK_f:
		case SDLK_g:
		case SDLK_h:
		case SDLK_i:
		case SDLK_j:
		case SDLK_k:
		case SDLK_l:
		case SDLK_m:
		case SDLK_n:
		case SDLK_o:
		case SDLK_p:
		case SDLK_q:
		case SDLK_r:
		case SDLK_s:
		case SDLK_t:
		case SDLK_u:
		case SDLK_v:
		case SDLK_w:
		case SDLK_x:
		case SDLK_y:
		case SDLK_z:if(mod & (KMOD_LSHIFT | KMOD_RSHIFT)) addChar('A'+ key - SDLK_a);else addChar('a'+ key - SDLK_a);break;
		case SDLK_0:
		case SDLK_1:
		case SDLK_2:
		case SDLK_3:
		case SDLK_4:
		case SDLK_5:
		case SDLK_6:
		case SDLK_7:
		case SDLK_8:
		case SDLK_9:
			if(!(mod & (KMOD_LSHIFT | KMOD_RSHIFT))) {
				addChar('0' + key - SDLK_0);
			} else {
				return false;
			}break;
		case SDLK_LEFT:moveLeft();break;
		case SDLK_RIGHT:moveRight();break;
		default:return false;break;
	}
	return true;
}


void EditField::addChar(char a)
{
	if(position>=28) {
		return;
	}
	text += a;
	++position;
	ani=5;
	editField->updateParameters(boost::assign::list_of(text));
}

void EditField::moveLeft()
{
	if(position>0) {
		--position;
	}
	ani=5;
}

void EditField::moveRight()
{
	if(position<28) {
		++position;
	}
	ani=5;
}

void EditField::removeCharBackspace()
{
	if(position>0) {
		--position;
	}
	ani=5;
	text = text.substr(0, position) + text.substr(position+1, text.length());
	editField->updateParameters(boost::assign::list_of(text));
}

void EditField::removeCharDelete()
{
	if(position>=text.length()) {
		return;
	}
	ani=5;
	text = text.substr(0, position) + text.substr(position+1, text.length());
	editField->updateParameters(boost::assign::list_of(text));
}

void EditField::draw(DC* const dc) const
{
	BOOST_ASSERT(dc);

	Object::draw(dc);
	if(SDL_Object::getFocus() != this) {
		return;
	}
	
	Rect entry_rect = Rect(Point(0,0), getOriginalRect().getSize());
//	if(entry_rect.Inside(mouse))
//		dc->setPen(*gui.lookUpPen(INNER_BORDER_HIGHLIGHT_PEN));
//	else
//		dc->setPen(*gui.lookUpPen(INNER_BORDER_PEN));
//	dc->setBrush(*gui.lookUpBrush(TRANSPARENT_BRUSH));
//	dc->DrawEdgedRoundedRectangle(Rect(100, 100, 200, 200), 4);

//  TODO	
//	dc->setPen(Pen(gui.lookUpColor(FORCE_TEXT_COLOR)->mixColor(dc->getSurface(), *gui.lookUpColor(BRIGHT_TEXT_COLOR), (unsigned int)(50*(sin(3.141*ani/10)+1))), 1, SOLID_PEN_STYLE));
//	dc->DrawVerticalLine(editField->getRelativePosition() + Point(5 + editField->getText()->getTextPosSize(position).getWidth(), 2), editField->getHeight()-3);
}

SDL_Object* EditField::checkHighlight(const Point& mouse) {
	if(!isShown()) {
		return NULL;
	}

	if(getAbsoluteRect().isTopLeftCornerInside(mouse)) {
		editField->setBrightnessHighlighted();
		descriptionText->setBrightnessHighlighted();
	} else {
		editField->resetBrightness();
		descriptionText->resetBrightness();
	}

	return Object::checkHighlight(mouse);
}

void EditField::process()
{
	if(!isShown()) {
		return;
	}

	Object::process();

	if(SDL_Object::getFocus() == editField) {
		SDL_Object::resetFocus();
	}
	if(SDL_Object::getFocus() != this) {
		editField->forceUnpress();
	}
	else {
		editField->forcePress();
	}
	++ani;
	editField->makePufferInvalid();
}


