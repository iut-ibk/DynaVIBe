/**
 * @file
 * @author  Michael Mair <michael.mair@uibk.ac.at>
 * @version 1.0
 * @section LICENSE
 *
 * This file is part of DynaMind
 *
 * Copyright (C) 2012  Michael Mair
 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include <simulatewithepanet.h>

//DynaMind includes
#include <dmsystem.h>
#include <dmlogsink.h>
#include <math.h>
#include <tbvectordata.h>

//CGAL
//#include <CGAL/Simple_cartesian.h>
//#include <CGAL/point_generators_2.h>
//#include <CGAL/Orthogonal_k_neighbor_search.h>
//#include <CGAL/Search_traits_2.h>
#include <list>
#include <cmath>

//Watersupply
#include <watersupplyviewdef.h>
#include <dmepanet.h>

using namespace DM;

DM_DECLARE_NODE_NAME(SimulateWithEPANET,Watersupply)

SimulateWithEPANET::SimulateWithEPANET()
{   
    //WS::ViewDefinitionHelper wsd;
    //this->addData("Watersupply", wsd.getAll(DM::MODIFY));
    //wsd.getCompleteView(WS::JUNCTION,DM::READ);
}

void SimulateWithEPANET::run()
{
    std::stringstream buffer;
    EPANET::Redirect re(&buffer);
    //write EPANET input file
    //std::string inputfile = "";

    //write Junctions
    //Logger(Debug) << WSSTRING[JUNCTION];

    int ret = EPANET::ENopen("/home/csae6550/Desktop/EN_goefis.inp","/home/csae6550/Desktop/EN_goefis.rpt","");
    ret+=EPANET::ENopenH();
    ret+=EPANET::ENinitH(1);
    ret+=EPANET::ENsolveH();
    //ret+=ENinitQ(1);
    //ret+=ENsolveQ();
    //ret+=ENcloseH();
    //ret+=ENcloseQ();
    ret+=EPANET::ENclose();
    Logger(Debug) << buffer.str();

    DM::Logger(DM::Debug) << "EPANET result: " << ret;
}
