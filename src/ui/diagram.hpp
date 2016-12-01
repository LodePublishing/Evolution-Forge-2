#ifndef _GUI_DIAGRAM_HPP
#define _GUI_DIAGRAM_HPP

#include "graphpoint.hpp"
#include "statictext.hpp"
#include "windowcolors.hpp"
#include "enums/graphtype.hpp"

#include "propertyfield.hpp"

class Diagram : public Object
{
	public:
		Diagram(SDL_Object* const diagram_parent, 
				const Rect& diagram_rect, 
				const Size distance_bottom_right, 
				const boost::shared_ptr<const WindowColors>& windowColors,
				const ePositionMode position_mode);
		~Diagram();

		void resetData();
		void process();
		void draw(DC* const dc) const;

		void reloadOriginalSize();

		void showValues(const bool show = true);

		void addItem(const boost::shared_ptr<const Text>& item_text, const boost::shared_ptr<const Text>& item_value_text, const std::string& item_value, const boost::shared_ptr<const Color>& text_color, const boost::shared_ptr<const Color>& value_color);
		void addGraph(const boost::shared_ptr<const Pen>& graph_pen, 
			const boost::shared_ptr<const Pen>& graph_dashed_pen, 
			const boost::shared_ptr<const Brush>& graph_brush, 
			const eGraphType graph_type);
		void setItemValues(const std::vector<std::string>& value_list);

		TODO
				void addLineGraph(const ePen graph_pen, const ePen graph_dashed_pen);
		void addBoxGraph();
		void addSecondBoxGraph(const ePen graph_pen, const eBrush graph_brush);

		std::vector<std::list<GraphPoint> >& getGraphList();
		std::vector<unsigned int> graphMax;

	private:
		std::vector<std::list<GraphPoint> > graphList;
		std::vector<eGraphType> graphType;
		std::vector<boost::shared_ptr<const Pen> > graphPen;
		std::vector<boost::shared_ptr<const Pen> > graphDashedPen;
		std::vector<boost::shared_ptr<const Brush> > graphBrush;
	
		std::vector<PropertyField*> itemText;

		const boost::shared_ptr<const WindowColors> windowColors;
	
		Diagram(const Diagram& object);
		Diagram& operator=(const Diagram& object);
};

inline std::vector<std::list<GraphPoint> >& Diagram::getGraphList() {
	return graphList;
}


#endif // _GUI_DIAGRAM_HPP
