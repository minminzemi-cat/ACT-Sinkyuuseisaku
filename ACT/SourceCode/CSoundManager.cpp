#include "CSoundManager.h"
#include "MyMacro.h"

CSoundManager::CSoundManager()
	: m_pSound()
{
	//インスタンス生成.
	for (int i = 0; i < enList::max; i++)
	{
		m_pSound[i] = new CSound();
	}
}

CSoundManager::~CSoundManager()
{
	Release();

	//インスタンスの破棄.
	for (int i = enList::max - 1; i >= 0; i--)
	{
		SAFE_DELETE(m_pSound[i]);
	}
}

//サウンドデータ読込関数.
bool CSoundManager::Load(HWND hWnd)
{
#if 0
	if (m_pSound[enList::BGM_Bonus]->Open(
		"Data\\Sound\\BGM\\BonusGameHouse.mp3",
		"BGM_Bonus",
		hWnd) == false)
	{
		return false;
	}
	if (m_pSound[enList::SE_Jump]->Open(
		"Data\\Sound\\SE\\Jump.wav",
		"SE_Jump",
		hWnd) == false)
	{
		return false;
	}
	if (m_pSound[enList::SE_Clear]->Open(
		"Data\\Sound\\SE\\Clear.wav",
		"SE_Clear",
		hWnd) == false)
	{
		return false;
	}
#else
	//サウンドリスト構造体
	//この関数内でしか使わないので関数内で定義.
	struct SoundList
	{
		int		listNo;		//enList列挙体を設定.
		char	path[256];	//ファイルの名前(パス付き).
		char	alias[32];	//エイリアス名.
	};
	//配列の初期化.
	//初期化の要素数によって自動計算されるので要素数を入力しなくてよい.
	SoundList SList[] =
	{
		{enList::SE_Jump,	"Data\\Sound\\SE\\Jump.wav",			"SE_Jump"		},
		{enList::BGM_Bonus,	"Data\\Sound\\BGM\\Gamemain.mp3",	    "BGM_Bonus"		},
		{enList::BGM_GameOver,	"Data\\Sound\\BGM\\gameover.mp3",	"BGM_GameOver"	},
		{enList::BGM_Ending,	"Data\\Sound\\BGM\\ending.mp3",	"BGM_Ending"	},
		{enList::SE_Clear,	"Data\\Sound\\SE\\Clear.wav",			"SE_Clear"		},
		{enList::SE_SP,	"Data\\Sound\\SE\\Spcual.mp3",			    "SE_SP"			},
		{enList::SE_Shot2,	"Data\\Sound\\SE\\Shot2.mp3",			"SE_Shot2"		},
		{enList::SE_KenMove,	"Data\\Sound\\SE\\KenMove.mp3",		"SE_KenMove"	},
		{enList::SE_Ken,	"Data\\Sound\\SE\\Ken.mp3",			    "SE_Ken"		},
		{enList::SE_GMAX,	"Data\\Sound\\SE\\GeageMAX.mp3",			"SE_GMAX"		},
		{enList::SE_Han,	"Data\\Sound\\SE\\han.mp3",			    "SE_Han"		},
		{enList::SE_Shot,	"Data\\Sound\\SE\\PShot.mp3",			"SE_Shot"		},
		{enList::SE_Dead,	"Data\\Sound\\SE\\PlayerDead.mp3",		"SE_Dead"		},
		{enList::SE_IAI,	"Data\\Sound\\SE\\iai.mp3",		"SE_IAI"		},
			//新しく読み込む必要があればここに追加する.順番は列挙型に依存しない.
	};
	//配列の最大要素数を算出(配列全体のサイズ/配列１つ分のサイズ).
	int list_max = sizeof(SList) / sizeof(SList[0]);
	//配列の最大数分処理する.
	for (int i = 0; i < list_max; i++)
	{
		if (m_pSound[SList[i].listNo]->Open(
			SList[i].path,
			SList[i].alias,
			hWnd) == false)
		{
			return false;
		}
	}
#endif
	return true;
}

//サウンドデータ解放関数.
void CSoundManager::Release()
{
	//開いた逆順で閉じる.
	for (int i = enList::max - 1; i >= 0; i--)
	{
		if (m_pSound[i] != nullptr) {
			m_pSound[i]->Close();
		}
	}
}