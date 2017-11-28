#include "stdafx.h"
#include "cSoundManager.h"

void cSoundManager::init()
{
	//���� �ý��� ����
	System_Create(&_system);

	//���� ä�μ� ����
	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//���� ä�� �����Ҵ�
	_sound = new Sound *[TOTALSOUNDBUFFER];
	_channel = new Channel *[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*)* (TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Channel*)* (TOTALSOUNDBUFFER));
}

void cSoundManager::release()
{
	if (_channel != nullptr || _sound != nullptr)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != nullptr)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != nullptr)
			{
				if (_sound[i]) _sound[i]->release();
			}
		}
	}

	SAFE_DELETE(_channel);
	SAFE_DELETE(_sound);

	//�ý��� �ݱ�
	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}
}

void cSoundManager::update()
{
	/*
	���� �ý����� ��� ������Ʈ ����� ������ �ٲ�ų�
	����� ���� ���带 ä�ο��� ������ �� �پ��� �۾��� �ڵ��������ش�.
	*/
	//���ΰ��ӿ��� ���� �Ŵ����� ������Ʈ ���ش�.
	_system->update();
}

void cSoundManager::render()
{
}

void cSoundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		//���
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, nullptr, &_sound[_mTotalSounds.size()]);
		}

		else//����Ʈ
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, nullptr, &_sound[_mTotalSounds.size()]);
		}
	}
	//����x ����Ʈ
	else
	{
		_system->createStream(soundName.c_str(), FMOD_DEFAULT, nullptr, &_sound[_mTotalSounds.size()]);
	}

	//�ʿ� ���带 Ű���� �Բ� ����ش�.
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void cSoundManager::play(string keyName, float volume)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//���� �÷���
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);
			//��������
			_channel[count]->setVolume(volume);
		}
	}
}

void cSoundManager::stop(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void cSoundManager::pause(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void cSoundManager::resume(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

bool cSoundManager::isPlaySound(string keyName)
{
	bool isPlay;
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool cSoundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}