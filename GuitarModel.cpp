///////////////////////////////////////////////////////////////////

#include "GuitarModel.h"

///////////////////////////////////////////////////////////////////

void
GuitarModel::init(const uint32_t iNumString, const uint32_t iNumFret)
{
	m_markerList.resize(iNumString);
	for (auto & m : m_markerList) m.resize(iNumFret);

	init_tuningDataMap();
	init_chordMap();
	init_scaleMap();
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::init_tuningDataMap()
{
	TuningData & td = m_tuningDataMap["standard"];

	td.m_tuning = getStdTuning();

	/////////////////////////
	{
		Physical phy;
		phy.m_pos =
		{
			Position(0,0),
			Position(1,8),
			Position(2,7),
			Position(3,6),
			Position(4,7),
			Position(5,0),
		};
		td.m_physicalMap["Hendrix Chord"] = phy;
	}
	/////////////////////////
	{
		Physical phy;
		phy.m_pos =
		{
			Position(0,0),
			Position(1,0),
			Position(2,0),
			Position(3,9),
			Position(4,7),
			Position(5,0),
		};
		td.m_physicalMap["E Minor High"] = phy;
	}
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::init_chordMap()
{
	{
		Chord c;
		c.m_offset = { 4, 3 };
		m_chordMap["Major Chord"] = c;
	}
	{
		Chord c;
		c.m_offset = { 3, 4 };
		m_chordMap["Minor Chord"] = c;
	}
	{
		Chord c;
		c.m_offset = { 4, 3, 3 };
		m_chordMap["Major 7th Chord"] = c;
	}
	{
		Chord c;
		c.m_offset = { 3, 4, 3 };
		m_chordMap["Minor 7th Chord"] = c;
	}
	{
		Chord c;
		c.m_offset = { 3, 6 };
		m_chordMap["Hendrix Triad"] = c;
	}
	{
		Chord c;
		c.m_offset = { 3, 1, 6 };
		m_chordMap["Hendrix Chord"] = c;
	}
	{
		Chord c;
		c.m_offset = { 4, 1 };
		m_chordMap["Major flat5 Chord"] = c;
	}
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::init_scaleMap()
{
	{
		Scale s;
		s.m_offset = { 2, 2, 1, 2, 2, 2 };
		m_scaleMap["Major Scale"] = s;
	}
	{
		Scale s;
		s.m_offset = { 2, 1, 2, 2, 1, 2 };
		m_scaleMap["Minor Scale"] = s;
	}
	{
		Scale s;
		s.m_offset = { 2, 1, 2, 2, 1, 3 };
		m_scaleMap["Harmonic Minor Scale"] = s;
	}
	{
		Scale s;
		s.m_offset = { 3, 2, 2, 3 };
		m_scaleMap["Pentatonic Minor Scale"] = s;
	}
	{
		Scale s;
		s.m_offset = { 2, 2, 3, 2 };
		m_scaleMap["Pentatonic Major Scale"] = s;
	}
	{
		Scale s;
		s.m_offset = { 3, 2, 1, 1, 3 };
		m_scaleMap["Blues Scale"] = s;
	}
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::setTuning(const std::string & iTuningName)
{
	m_tuningName = iTuningName;
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::setMarkerList(MarkerList & iMarkerList)
{
	for (uint32_t u0=0; u0<m_markerList.size(); u0++) {
		for (uint32_t u1=0; u1<m_markerList[u0].size(); u1++) {
			if (iMarkerList[u0][u1].type != 0) {
				m_markerList[u0][u1] = iMarkerList[u0][u1];
			}
		}
	}
}

///////////////////////////////////////////////////////////////////

std::vector<GuitarModel::Note>
GuitarModel::getStdTuning()
{
	std::vector<GuitarModel::Note> tuning =
	{
		Note::E,
		Note::B,
		Note::G,
		Note::D,
		Note::A,
		Note::E
	};
	return(tuning);
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::getPhysicalNames(std::vector<std::string> & oNames)
{
	TuningData & td = m_tuningDataMap[m_tuningName];
	for (auto i : td.m_physicalMap) oNames.push_back(i.first);
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::getChordNames(std::vector<std::string> & oNames)
{
	for (auto i : m_chordMap) oNames.push_back(i.first);
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::getScaleNames(std::vector<std::string> & oNames)
{
	for (auto i : m_scaleMap) oNames.push_back(i.first);
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::applyPhysical(const std::string & iName)
{
	TuningData & td = m_tuningDataMap[m_tuningName];
	const Physical & physical = td.m_physicalMap[iName];

	for (const auto & pos : physical.m_pos) {
		Marker & marker = m_markerList[pos.m_string][pos.m_fret];
		marker.type = 1;
	}
}

///////////////////////////////////////////////////////////////////

GuitarModel::Note
getNote(const std::string & iNote)
{
	GuitarModel::Note note = GuitarModel::Note::A;
	if (iNote=="A") note = GuitarModel::Note::A;
	if (iNote=="A#") note = GuitarModel::Note::A_SHARP;
	if (iNote=="B") note = GuitarModel::Note::B;
	if (iNote=="C") note = GuitarModel::Note::C;
	if (iNote=="C#") note = GuitarModel::Note::C_SHARP;
	if (iNote=="D") note = GuitarModel::Note::D;
	if (iNote=="D#") note = GuitarModel::Note::D_SHARP;
	if (iNote=="E") note = GuitarModel::Note::E;
	if (iNote=="F") note = GuitarModel::Note::F;
	if (iNote=="F#") note = GuitarModel::Note::F_SHARP;
	if (iNote=="G") note = GuitarModel::Note::G;
	if (iNote=="G#") note = GuitarModel::Note::G_SHARP;
	return(note);
}

///////////////////////////////////////////////////////////////////

std::string
getNoteStr(const GuitarModel::Note iNote)
{
	switch (iNote) {
		case GuitarModel::Note::A: return("A");
		case GuitarModel::Note::A_SHARP: return("A#");
		case GuitarModel::Note::B: return("B");
		case GuitarModel::Note::C: return("C");
		case GuitarModel::Note::C_SHARP: return("C#");
		case GuitarModel::Note::D: return("D");
		case GuitarModel::Note::D_SHARP: return("D#");
		case GuitarModel::Note::E: return("E");
		case GuitarModel::Note::F: return("F");
		case GuitarModel::Note::F_SHARP: return("F#");
		case GuitarModel::Note::G: return("G");
		case GuitarModel::Note::G_SHARP: return("G#");
	}
	return("?");
}

///////////////////////////////////////////////////////////////////

GuitarModel::Note
getNoteOffset(const GuitarModel::Note & iNote, const uint32_t iOffset)
{
	uint32_t unote = (uint32_t)iNote;
	unote += iOffset;
	if (unote > 11) unote = (unote-12);
	return((GuitarModel::Note)unote);
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::getPositions(const Note & iNote, std::vector<Position> & oPos)
{
	TuningData & td = m_tuningDataMap[m_tuningName];
	for (uint32_t u0=0; u0<m_markerList.size(); u0++) {
		Note note = td.m_tuning[u0];
		for (uint32_t u1=0; u1<m_markerList[u0].size(); u1++) {
			if (note == iNote) {
				oPos.push_back(Position(u0,u1));
			}
			note = getNoteOffset(note, 1);
		}
	}
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::applyChord(const std::string & iName, const std::string & iNote)
{
	GuitarModel::Note note = ::getNote(iNote);
	Chord & chord = m_chordMap[iName];

	NoteSet noteSet;

	noteSet.insert(note);

	for (const auto & ofs : chord.m_offset) {
		note = getNoteOffset(note, ofs);
		noteSet.insert(note);
	}

	for (const auto & n : noteSet) {
		std::vector<Position> poslist;
		getPositions(n, poslist);
		for (const auto & pos : poslist) {
			Marker & marker = m_markerList[pos.m_string][pos.m_fret];
			marker.type = 1;
		}
	}
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::applyScale(const std::string & iName, const std::string & iNote)
{
	GuitarModel::Note note = ::getNote(iNote);
	Scale & scale = m_scaleMap[iName];

	NoteSet noteSet;

	noteSet.insert(note);

	for (const auto & ofs : scale.m_offset) {
		note = getNoteOffset(note, ofs);
		noteSet.insert(note);
	}

	for (const auto & n : noteSet) {
		std::vector<Position> poslist;
		getPositions(n, poslist);
		for (const auto & pos : poslist) {
			Marker & marker = m_markerList[pos.m_string][pos.m_fret];
			marker.type = 1;
		}
	}
}

///////////////////////////////////////////////////////////////////

GuitarModel::Note
GuitarModel::getNote(const uint32_t iString, const uint32_t iFret)
{
	TuningData & td = m_tuningDataMap[m_tuningName];
	Note note = td.m_tuning[iString];
	note = getNoteOffset(note, iFret);
	return(note);
}

///////////////////////////////////////////////////////////////////

std::string
GuitarModel::getNoteStr(const uint32_t iString, const uint32_t iFret)
{
	return(::getNoteStr(getNote(iString,iFret)));
}

///////////////////////////////////////////////////////////////////

void GuitarModel::toggleMarker(const uint32_t iString, const uint32_t iFret)
{
	Marker & marker = m_markerList[iString][iFret];

	if (marker.type == 0) {
		marker.type = 1;
	} else {
		marker.type = 0;
	}
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::expand()
{
	NoteSet noteSet;

	for (uint32_t u0=0; u0<m_markerList.size(); u0++) {
		for (uint32_t u1=0; u1<m_markerList[u0].size(); u1++) {
			Marker & marker = m_markerList[u0][u1];
			if (marker.type == 0) continue;
			Note note = getNote(u0, u1);
			noteSet.insert(note);
		}
	}

	for (const auto & n : noteSet) {
		std::vector<Position> poslist;
		getPositions(n, poslist);
		for (const auto & pos : poslist) {
			Marker & marker = m_markerList[pos.m_string][pos.m_fret];
			marker.type = 1;
		}
	}
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::clear()
{
	for (uint32_t u0=0; u0<m_markerList.size(); u0++) {
		for (uint32_t u1=0; u1<m_markerList[u0].size(); u1++) {
			Marker & marker = m_markerList[u0][u1];
			marker.type = 0;
		}
	}
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::search(
	std::vector<std::string> & oPatternList,
	std::vector<std::string> & oNoteList,
	std::vector<std::string> & oNameList,
	const bool iVal_2,
	const bool iVal_3,
	const bool iVal_4,
	const bool iVal_5,
	const bool iVal_6,
	const bool iVal_7,
	const bool iVal_8,
	const bool iVal_phy,
	const bool iVal_chords,
	const bool iVal_scales,
	const bool iVal_inexact,
	const std::string & iVal_inexactval
	)
{
	NoteSet noteSet;

	for (uint32_t u0=0; u0<m_markerList.size(); u0++) {
		for (uint32_t u1=0; u1<m_markerList[u0].size(); u1++) {
			Marker & marker = m_markerList[u0][u1];
			if (marker.type == 0) continue;
			Note note = getNote(u0, u1);
			noteSet.insert(note);
		}
	}

	bool ok;
	TuningData & td = m_tuningDataMap[m_tuningName];

	for (const auto & i : td.m_physicalMap) {
		NoteSet phyNoteSet;
		getNoteSet(i.second.m_pos, phyNoteSet);

		ok = match(
			PHYSICAL,
			noteSet,
			phyNoteSet,
			iVal_2,
			iVal_3,
			iVal_4,
			iVal_5,
			iVal_6,
			iVal_7,
			iVal_8,
			iVal_phy,
			iVal_chords,
			iVal_scales,
			iVal_inexact,
			iVal_inexactval);

		if (ok) {
			oPatternList.push_back("Physical");
			oNoteList.push_back("-");
			oNameList.push_back(i.first);
		}
	}

	for (const auto & i : m_chordMap) {
		for (Note note=Note::A; note<=Note::G_SHARP; note = (Note)(note+1)) {
			NoteSet chordNoteSet;
			getNoteSet(note, i.second.m_offset, chordNoteSet);

			ok = match(
				CHORD,
				noteSet,
				chordNoteSet,
				iVal_2,
				iVal_3,
				iVal_4,
				iVal_5,
				iVal_6,
				iVal_7,
				iVal_8,
				iVal_phy,
				iVal_chords,
				iVal_scales,
				iVal_inexact,
				iVal_inexactval);

			if (ok) {
				oPatternList.push_back("Chord");
				oNoteList.push_back(::getNoteStr(note));
				oNameList.push_back(i.first);
			}
		}
	}

	for (const auto & i : m_scaleMap) {
		for (Note note=Note::A; note<=Note::G_SHARP; note = (Note)(note+1)) {
			NoteSet scaleNoteSet;
			getNoteSet(note, i.second.m_offset, scaleNoteSet);

			ok = match(
				SCALE,
				noteSet,
				scaleNoteSet,
				iVal_2,
				iVal_3,
				iVal_4,
				iVal_5,
				iVal_6,
				iVal_7,
				iVal_8,
				iVal_phy,
				iVal_chords,
				iVal_scales,
				iVal_inexact,
				iVal_inexactval);

			if (ok) {
				oPatternList.push_back("Scale");
				oNoteList.push_back(::getNoteStr(note));
				oNameList.push_back(i.first);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////

bool
GuitarModel::match(
	const PatternType iPatternType,
	const NoteSet & iInputSet,
	const NoteSet & iPatternSet,
	const bool iVal_2,
	const bool iVal_3,
	const bool iVal_4,
	const bool iVal_5,
	const bool iVal_6,
	const bool iVal_7,
	const bool iVal_8,
	const bool iVal_phy,
	const bool iVal_chords,
	const bool iVal_scales,
	const bool iVal_inexact,
	const std::string & iVal_inexactval
	)
{
	if ((iPatternType==PHYSICAL) && (!iVal_phy)) return(false);
	if ((iPatternType==CHORD) && (!iVal_chords)) return(false);
	if ((iPatternType==SCALE) && (!iVal_scales)) return(false);

	uint32_t matchCount = 0;

	for (const auto & note1 : iInputSet) {
		for (const auto & note2 : iPatternSet) {
			if (note1==note2) matchCount++;
		}
	}

	if (matchCount <= 1) return(false);

	uint32_t setSize = iInputSet.size();
	if (iInputSet.size() > iPatternSet.size()) setSize = iPatternSet.size();

	if (!iVal_inexact) {
		if (matchCount != setSize) return(false);
	} else {
		uint32_t inexactval = std::stoul(iVal_inexactval);
		uint32_t size = 0;
		if (setSize > inexactval) {
			size = setSize - inexactval;
		}
		if (matchCount < size) return(false);
	}

	if ((iVal_2) && (iPatternSet.size()==2)) return(true);
	if ((iVal_3) && (iPatternSet.size()==3)) return(true);
	if ((iVal_4) && (iPatternSet.size()==4)) return(true);
	if ((iVal_5) && (iPatternSet.size()==5)) return(true);
	if ((iVal_6) && (iPatternSet.size()==6)) return(true);
	if ((iVal_7) && (iPatternSet.size()==7)) return(true);
	if ((iVal_8) && (iPatternSet.size()>=8)) return(true);

	return(false);
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::getNoteSet(const std::vector<Position> & iPos, NoteSet & oNoteSet)
{
	Note note;
	for (const auto & pos : iPos) {
		note = getNote(pos.m_string, pos.m_fret);
		oNoteSet.insert(note);
	}
}

///////////////////////////////////////////////////////////////////

void
GuitarModel::getNoteSet(const Note iBaseNote, const std::vector<uint8_t> & iOfs, NoteSet & oNoteSet)
{
	oNoteSet.insert(iBaseNote);
	Note note = iBaseNote;
	for (const auto & ofs : iOfs) {
		note = getNoteOffset(note, ofs);
		oNoteSet.insert(note);
	}
}

///////////////////////////////////////////////////////////////////
