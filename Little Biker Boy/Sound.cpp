// Sound.cpp: implementation of the CSound class.
//
//////////////////////////////////////////////////////////////////////

#include "stdAfx.h"
#include "Sound.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSound::CSound()
{	
/*	m_pDirectAudioPerformance = NULL;
	m_pDirectAudioLoader = NULL;
	m_pSegment = NULL;
	m_pGraph = NULL;
	m_pMediaControl = NULL;
	m_pMediaPosition = NULL;*/
	m_enumFormat = Unknown;
}
/*
void CSound::InitialiseForWavMidi(IDirectMusicPerformance8* pDirectAudioPerformance, IDirectMusicLoader8* pDirectAudioLoader)
{
	m_pDirectAudioPerformance = pDirectAudioPerformance;
	m_pDirectAudioLoader = pDirectAudioLoader;

	m_enumFormat = WavMidi;
}
*/
void CSound::InitialiseForMP3()
{
/*	CoCreateInstance(CLSID_FilterGraph, NULL,
                     CLSCTX_INPROC, IID_IGraphBuilder, (void**)&m_pGraph);

	m_pGraph->QueryInterface(IID_IMediaControl, (void**)&m_pMediaControl);

	m_pGraph->QueryInterface(IID_IMediaPosition, (void**)&m_pMediaPosition);

	m_enumFormat = MP3;*/
}


CSound::~CSound()
{
/*	Stop();

	SafeRelease(m_pSegment);
	SafeRelease(m_pGraph);
	SafeRelease(m_pMediaControl);
	SafeRelease(m_pMediaPosition);
*/
//	LogInfo("<li>Sound destroyed OK");
}

bool CSound::LoadSound(const char* szSoundFileName)
{
/*	WCHAR wstrSoundPath[MAX_PATH];
	CHAR strSoundPath[MAX_PATH];

	switch(m_enumFormat)
	{
		case MP3:
			//Get the our applications "sounds" directory.
			GetCurrentDirectory(MAX_PATH, strSoundPath);
			strcat(strSoundPath, "\\");
			strcat(strSoundPath, szSoundFileName);

			//Convert the path to unicode.
			MultiByteToWideChar(CP_ACP, 0, strSoundPath, -1, wstrSoundPath, MAX_PATH);
				
			//MB(strSoundPath);
			m_pGraph->RenderFile(wstrSoundPath, NULL);
		break;
		case WavMidi:

			//Convert the filename to unicode.	
			MultiByteToWideChar(CP_ACP, 0, "dig.wav", -1, wstrSoundPath, MAX_PATH);
			
			//Load a sound
			m_pDirectAudioLoader->LoadObjectFromFile(	CLSID_DirectMusicSegment, IID_IDirectMusicSegment8,
														wstrSoundPath, (void**) &m_pSegment);

			m_pSegment->Download(m_pDirectAudioPerformance);

		break;
		default:
			return false;
	}
*/
	return true;
}

bool CSound::Play(DWORD dwNumOfRepeats)
{

/*	switch(m_enumFormat)
	{
		case MP3:
			//Make sure that we are at the start of the stream
			m_pMediaPosition->put_CurrentPosition(0);
			
			//Play mp3
			m_pMediaControl->Run();
		break;
		case WavMidi:
			//Set the number of times the sound repeats
			m_pSegment->SetRepeats(dwNumOfRepeats);		//To loop the sound forever, pass in DMUS_SEG_REPEAT_INFINITE

			//Play the loaded sound
			m_pDirectAudioPerformance->PlaySegmentEx(m_pSegment, NULL, NULL, 0, 0, NULL, NULL, NULL);
		break;
		default:
			return false;
	}
*/
	return true;
}
/*
bool CSound::Stop()
{
	switch(m_enumFormat)
	{
		case MP3:
			m_pMediaControl->Stop();
		break;
		case WavMidi:
			//Stop the loaded sound
			m_pDirectAudioPerformance->StopEx(m_pSegment, 0, 0);
		break;
		default:
			return false;
	}

	return true;
}

bool CSound::IsPlaying()
{
	switch(m_enumFormat)
	{
		case MP3:
			REFTIME refPosition;
			REFTIME refDuration;

			m_pMediaPosition->get_CurrentPosition(&refPosition);
			m_pMediaPosition->get_Duration(&refDuration);
			
			if(refPosition < refDuration)
			{
				return true;
			}
			else
			{
				return false;
			}
		break;
		case WavMidi:
			if(m_pDirectAudioPerformance->IsPlaying(m_pSegment, NULL) == S_OK)
			{
				return true;
			}
			else
			{
				return false;
			}
		break;
		default:
			return false;
	}
}
*/