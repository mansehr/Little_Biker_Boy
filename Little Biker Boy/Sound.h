// Sound.h: interface for the CSound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUND_H__C89CE19D_7C1D_4741_BE61_5AD0836FCF3A__INCLUDED_)
#define AFX_SOUND_H__C89CE19D_7C1D_4741_BE61_5AD0836FCF3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSound
{
public:
	bool IsPlaying();
	bool Stop();
	bool Play(DWORD dwNumOfRepeats = 0);
	bool LoadSound(const char* szSoundFilePath);
	//void InitialiseForWavMidi(IDirectMusicPerformance8* pDirectAudioPerformance, IDirectMusicLoader8* pDirectAudioLoader);
	void InitialiseForMP3();
	CSound();				//Use this constructor for mp3 files
	virtual ~CSound();

private:
	enum Format {Unknown, MP3, WavMidi};
	/*IDirectMusicSegment8* m_pSegment;
	IDirectMusicPerformance8* m_pDirectAudioPerformance;	
	IDirectMusicLoader8* m_pDirectAudioLoader;
	IGraphBuilder* m_pGraph;
	IMediaControl* m_pMediaControl;
	IMediaPosition* m_pMediaPosition;*/
	Format m_enumFormat;
};

#endif // !defined(AFX_SOUND_H__C89CE19D_7C1D_4741_BE61_5AD0836FCF3A__INCLUDED_)
