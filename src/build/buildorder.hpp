#ifndef _BUILD_BUILDORDER_HPP
#define _BUILD_BUILDORDER_HPP

#if 0

#include "prebuildorder.hpp"

class BUILDORDER : public PREBUILDORDER
{
	private:
	       	unsigned int mutationRate;
       		const bool buildGene(const unsigned int build_unit);
		unsigned int pFitness;
		unsigned int sFitness;
		unsigned int tFitness;
		
		const bool buildIt(const unsigned int build_unit);
	public:
		BUILDORDER();
		~BUILDORDER();
		BUILDORDER& operator=(const BUILDORDER& object);
		BUILDORDER(const BUILDORDER& object);
		void resetData();
//Output:
		void setpFitness(const unsigned int p_fitness);
		void setsFitness(const unsigned int s_fitness);
		void settFitness(const unsigned int t_fitness);

		const unsigned int calculateSecondaryFitness() const; //?

		const unsigned int getpFitness() const;
		const unsigned int getsFitness() const;
		const unsigned int gettFitness() const;
//Controls:
		const bool calculateStep(); 
//		void resetGeneCode();//resets either to a pre-processed buildorder or a completely random one*/
		void prepareForNewGeneration(); //resets all data to standard values
//		void crossOver(BUILDORDER* parent2, BUILDORDER* child1, BUILDORDER* child2);
};

// ----------------------------------------------------
// ------ PRETTY UNINTERESTING SET/GET FUNCTIONS ------
// ----------------------------------------------------

inline void BUILDORDER::setpFitness(const unsigned int p_fitness) 
{
#ifdef _SCC_DEBUG
	if(p_fitness > MAX_PFITNESS) {
		toLog("DEBUG: (BUILDORDER::setpFitness): Value p_fitness out of range.");return;
	}
#endif
	pFitness = p_fitness;
}

inline void BUILDORDER::setsFitness(const unsigned int s_fitness)
{
#ifdef _SCC_DEBUG
	if(s_fitness > MAX_MINERALS+MAX_GAS) {
		toLog("DEBUG: (BUILDORDER::setsFitness): Value s_fitness out of range.");return;
	}
#endif
	sFitness = s_fitness;
}

inline void BUILDORDER::settFitness(const unsigned int t_fitness)
{
#ifdef _SCC_DEBUG
        if(t_fitness > MAX_TFITNESS) {
                toLog("DEBUG: (BUILDORDER::settFitness): Value t_fitness out of range.");return;
        }
#endif
        tFitness = t_fitness;
}


inline const unsigned int BUILDORDER::getpFitness() const
{
#ifdef _SCC_DEBUG
	if(pFitness > MAX_PFITNESS) {
		toLog("DEBUG: (BUILDORDER::getpFitness): Variable pFitness not initialized.");return(0);
	}
#endif
	return(pFitness);
}

inline const unsigned int BUILDORDER::getsFitness() const
{
#ifdef _SCC_DEBUG
	if(sFitness>MAX_MINERALS+MAX_GAS) {
		toLog("DEBUG: (BUILDORDER::getsFitness): Variable sFitness not initialized.");return(0);
	}
#endif
	return(sFitness);
}

inline const unsigned int BUILDORDER::gettFitness() const
{
#ifdef _SCC_DEBUG
        if(tFitness>MAX_TFITNESS) {
                toLog("DEBUG: (BUILDORDER::gettFitness): Variable tFitness not initialized.");return(0);
        }
#endif
        return(tFitness);
}

#endif


#endif //_BUILD_BUILDORDER_HPP


#if 0
void DATABASE::saveBuildOrder(const std::string& name, const ANABUILDORDER* anarace) const
{
	std::ostringstream os;
	os.str("");
#ifdef __linux__
	os << "output/bos/";
	os << raceString[anarace->getRace()] << "/" << name << ".html";
#elif WIN32
	os << "output\\bos\\";
	os << raceString[anarace->getRace()] << "\\" << name << ".html";
#endif
	std::ofstream pFile(os.str().c_str(), std::ios_base::out | std::ios_base::trunc);
	
	if(!pFile.is_open())
	{
		toLog("ERROR: (DATABASE::saveBuildOrder) Could not create file " + os.str() + " (write protection? disk space?)");
		return;
	}
	
	pFile << "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">" << std::endl;
	pFile << "<html>" << std::endl;
	pFile << "<head>" << std::endl;
	pFile << "  <meta content=\"text/html; charset=ISO-8859-1\"" << std::endl;
	pFile << " http-equiv=\"content-type\">" << std::endl;
	pFile << "  <title>Build order list</title>" << std::endl;
	pFile << "</head>" << std::endl;
	pFile << "<body alink=\"#000099\" vlink=\"#990099\" link=\"#000099\" style=\"color: rgb("<< (int)UI_Object::theme.lookUpColor(BRIGHT_TEXT_COLOR)->r() << ", " << (int)UI_Object::theme.lookUpColor(BRIGHT_TEXT_COLOR)->g() << ", " << (int)UI_Object::theme.lookUpColor(BRIGHT_TEXT_COLOR)->b() << "); background-color: rgb(" << (int)UI_Object::theme.lookUpBrush(WINDOW_BACKGROUND_BRUSH)->GetColor()->r() << ", " << (int)UI_Object::theme.lookUpBrush(WINDOW_BACKGROUND_BRUSH)->GetColor()->g() << ", " << (int)UI_Object::theme.lookUpBrush(WINDOW_BACKGROUND_BRUSH)->GetColor()->b() << ");\">" << std::endl;
	pFile << "<div style=\"text-align: center;\"><big style=\"font-weight: bold;\"><big>Evolution Forge " << CORE_VERSION << "</big></big><br><br>" << std::endl;
	pFile << "<big>Buildorder list " << name << "</big><br>" << std::endl;
	pFile << "</div>" << std::endl;
	pFile << "<br>" << std::endl;
	pFile << "<table style=\"background-color: rgb(" << (int)UI_Object::theme.lookUpBrush(WINDOW_FOREGROUND_BRUSH)->GetColor()->r() << ", " << (int)UI_Object::theme.lookUpBrush(WINDOW_FOREGROUND_BRUSH)->GetColor()->g() << ", " << (int)UI_Object::theme.lookUpBrush(WINDOW_FOREGROUND_BRUSH)->GetColor()->b() << "); text-align: center; vertical-align: middle; width: 600px; margin-left: auto; margin-right: auto;\""<< std::endl;
	pFile << " border=\"1\" cellspacing=\"0\" cellpadding=\"1\">" << std::endl;
	pFile << "  <tbody>" << std::endl;
	pFile << "	<tr>" << std::endl;
	pFile << "	  <td style=\"text-align: center; vertical-align: middle; width: 200px;\">" << UI_Object::theme.lookUpString(OUTPUT_UNITNAME_STRING) << "<br>" << std::endl;
	pFile << "	  </td>" << std::endl;
	pFile << "	  <td style=\"text-align: center; vertical-align: middle; width: 75px;\">" << UI_Object::theme.lookUpString(OUTPUT_SUPPLY_STRING) << "</td>" << std::endl;
	pFile << "	  <td style=\"text-align: center; vertical-align: middle; width: 75px;\">" << UI_Object::theme.lookUpString(OUTPUT_MINERALS_STRING) << "<br>" << std::endl;
	pFile << "	  </td>" << std::endl;
	pFile << "	  <td style=\"text-align: center; vertical-align: middle; width: 75px;\">" << UI_Object::theme.lookUpString(OUTPUT_GAS_STRING) << "<br>" << std::endl;
	pFile << "	  </td>" << std::endl;
	pFile << "	  <td style=\"text-align: center; vertical-align: middle; width: 100px;\">" << UI_Object::theme.lookUpString(OUTPUT_LOCATION_STRING) << "<br>" << std::endl;
	pFile << "	  </td>" << std::endl;
	pFile << "	  <td style=\"text-align: center; vertical-align: middle; width: 75px;\">" << UI_Object::theme.lookUpString(OUTPUT_TIME_STRING) << "<br>" << std::endl;
	pFile << "	  </td>" << std::endl;
	pFile << "	</tr>" << std::endl;

	for(std::list<PROGRAM>::const_iterator order = anarace->programList.begin(); order != anarace->programList.end(); ++order)
	{
		pFile << "	<tr style=\"text-align: center; vertical-align: middle; background-color: rgb(" << (int)UI_Object::theme.lookUpBrush((eBrush)(UNIT_TYPE_0_BRUSH+stats[anarace->getRace()][order->getUnit()].unitType))->GetColor()->r() << ", " << (int)UI_Object::theme.lookUpBrush((eBrush)(UNIT_TYPE_0_BRUSH+stats[anarace->getRace()][order->getUnit()].unitType))->GetColor()->g() << ", " << (int)UI_Object::theme.lookUpBrush((eBrush)(UNIT_TYPE_0_BRUSH+stats[anarace->getRace()][order->getUnit()].unitType))->GetColor()->b() << ");\">" << std::endl;
		pFile << "	  <td style=\"\">" << UI_Object::theme.lookUpString((eString)(UNIT_TYPE_COUNT*anarace->getRace() + order->getUnit() + UNIT_NULL_STRING)) << "<br>" << std::endl;
		pFile << "	  </td>" << std::endl;
		pFile << "	  <td style=\"\">" << order->getStatisticsBefore().getNeedSupply() << "/" << order->getStatisticsBefore().getHaveSupply() << "<br>" << std::endl;
		pFile << "	  </td>" << std::endl;

		pFile << "	  <td style=\"\">" << order->getStatisticsBefore().getHaveMinerals()/100 << "<br>" << std::endl;
		pFile << "	  </td>" << std::endl;

		pFile << "	  <td style=\"\">" << order->getStatisticsBefore().getHaveGas()/100 << "<br>" << std::endl;
		pFile << "	  </td>" << std::endl;

		pFile << "	  <td style=\"\">" << (*anarace->getMap())->getLocation(order->getLocation())->getName() << "<br>" << std::endl;
		pFile << "	  </td>" << std::endl;

		pFile << "	  <td style=\"\">" << formatTime(order->getRealTime()) << "<br>" << std::endl;
		pFile << "	  </td>" << std::endl;
																								   
		pFile << "	</tr>" << std::endl;
	}

	pFile << "  </tbody>" << std::endl;
	pFile << "</table>" << std::endl;
	pFile << "<br>" << std::endl;
	pFile << "<b><a href=\"http://www.clawsoftware.de\">www.clawsoftware.de</a></b>\n";
	pFile << "</body>\n";
	pFile << "</html>" << std::endl;
}
#endif