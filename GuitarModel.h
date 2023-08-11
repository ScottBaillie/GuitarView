///////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstdint>

///////////////////////////////////////////////////////////////////

class GuitarModel
{
public:
	//////////

	enum Note
	{
		A,
		A_SHARP,
		B,
		C,
		C_SHARP,
		D,
		D_SHARP,
		E,
		F,
		F_SHARP,
		G,
		G_SHARP
	};

	typedef std::vector<Note>	NoteList;
	typedef std::set<Note>		NoteSet;

	//////////

	enum PatternType
	{
		PHYSICAL,
		CHORD,
		SCALE
	};

	//////////

	class Position
	{
	public:
		Position(const uint32_t iString, const uint32_t iFret) {m_string=iString; m_fret=iFret;}

	public:
		uint32_t	m_string;
		uint32_t	m_fret;
	};

	//////////

	class Physical
	{
	public:
		std::vector<Position>	m_pos;
	};

	typedef std::map<std::string,Physical>	PhysicalMap;

	//////////

	class Chord
	{
	public:
		std::vector<uint8_t>	m_offset;
	};

	typedef std::map<std::string,Chord>	ChordMap;

	//////////

	class Scale
	{
	public:
		std::vector<uint8_t>	m_offset;
	};

	typedef std::map<std::string,Scale>	ScaleMap;

	//////////

	class TuningData
	{
	public:
		NoteList		m_tuning;
		PhysicalMap		m_physicalMap;
	};

	typedef std::map<std::string,TuningData>	TuningDataMap;

	//////////

	struct Marker
	{
		uint32_t type = 0;
	};

	typedef std::vector<std::vector<Marker> >	MarkerList;

	//////////

public:
	void init(const uint32_t iNumString, const uint32_t iNumFret);

	void setTuning(const std::string & iTuningName);

	void getPhysicalNames(std::vector<std::string> & oNames);
	void getChordNames(std::vector<std::string> & oNames);
	void getScaleNames(std::vector<std::string> & oNames);

	void applyPhysical(const std::string & iName);
	void applyChord(const std::string & iName, const std::string & iNote);
	void applyScale(const std::string & iName, const std::string & iNote);

	Note getNote(const uint32_t iString, const uint32_t iFret);
	std::string getNoteStr(const uint32_t iString, const uint32_t iFret);

	const MarkerList & getMarkerList() { return(m_markerList); }
	void setMarkerList(MarkerList & iMarkerList);

	void toggleMarker(const uint32_t iString, const uint32_t iFret);
	void expand();
	void clear();

	void search(
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
		);

private:
	void init_tuningDataMap();
	void init_chordMap();
	void init_scaleMap();
	std::vector<GuitarModel::Note> getStdTuning();
	void getPositions(const Note & iNote, std::vector<Position> & oPos);

	void getNoteSet(const std::vector<Position> & iPos, NoteSet & oNoteSet);
	void getNoteSet(const Note iBaseNote, const std::vector<uint8_t> & iOfs, NoteSet & oNoteSet);

	bool match(
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
		);

private:
	std::string		m_tuningName;
	MarkerList		m_markerList;
	TuningDataMap		m_tuningDataMap;
	ChordMap		m_chordMap;
	ScaleMap		m_scaleMap;
};

///////////////////////////////////////////////////////////////////
