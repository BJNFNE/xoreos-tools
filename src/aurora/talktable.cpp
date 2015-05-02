/* xoreos-tools - Tools to help with xoreos development
 *
 * xoreos-tools is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * xoreos-tools is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * xoreos-tools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xoreos-tools. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *  Base class for BioWare's talk tables.
 */

#include "src/common/util.h"
#include "src/common/stream.h"

#include "src/aurora/aurorafile.h"
#include "src/aurora/talktable.h"
#include "src/aurora/talktable_tlk.h"
#include "src/aurora/talktable_gff.h"

static const uint32 kTLKID = MKTAG('T', 'L', 'K', ' ');
static const uint32 kGFFID = MKTAG('G', 'F', 'F', ' ');

namespace Aurora {

TalkTable::TalkTable(Common::Encoding encoding) : _encoding(encoding) {
}

TalkTable::~TalkTable() {
}

TalkTable *TalkTable::load(Common::SeekableReadStream &tlk, Common::Encoding encoding) {
	uint32 pos = tlk.pos();

	uint32 id, version;
	bool utf16le;

	AuroraBase::readHeader(tlk, id, version, utf16le);

	tlk.seek(pos);

	if (id == kTLKID) {
		if (encoding == Common::kEncodingInvalid)
			encoding = Common::kEncodingCP1252;

		return new TalkTable_TLK(tlk, encoding);
	}

	if (id == kGFFID) {
		if (encoding == Common::kEncodingInvalid)
			encoding = Common::kEncodingUTF16LE;

		return new TalkTable_GFF(tlk, encoding);
	}

	return 0;
}

} // End of namespace Aurora
