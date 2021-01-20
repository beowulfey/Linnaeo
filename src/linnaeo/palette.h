#ifndef PALETTE_H
#define PALETTE_H

#include <QPalette>

namespace Palette
/// Sequence Namespace
/// Sequences are stored in Linnaeo (as data in my Item Models) as QStrings for simplicity.
/// These utilities are provided for validation purposes.
{
QPalette getPalette();
QPalette getDarkPalette();
}



#endif // PALETTE_H
