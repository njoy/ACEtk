// xsdir
#include "ACEtk/Xsdir.hpp"

// generic ACE table
#include "ACEtk/State.hpp"
#include "ACEtk/Table.hpp"
#include "ACEtk/fromFile.hpp"

// enumerators
#include "ACEtk/ReferenceFrame.hpp"

// ACE data blocks
#include "ACEtk/block.hpp"

// interpretation ACE tables
#include "ACEtk/ContinuousEnergyTable.hpp"

#ifndef ACETK_HPP
#define ACETK_HPP

#include <istream>
#include <iterator>
#include <functional>
#include <algorithm>

#include "range/v3/all.hpp"

#include "dimwits.hpp"
#include "interpolation.hpp"
#include "header-utilities.hpp"
#include "Log.hpp"

namespace njoy {
namespace ACEtk {

using namespace dimwits;

#include "ACEtk/details.hpp"
#include "ACEtk/interpretation.hpp"

}
}

#endif
