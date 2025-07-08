#include "stdafx.h"
#include "GameUiBase.h"

void GameUiBase::DrawListSprites(RenderContext& rc)
{

	//スプライトリストのイテレーター
	auto spriteIter = m_spriteList.begin();
	//フォントリストのイテレーター
	auto fontIter = m_fontList.begin();

	while (spriteIter != m_spriteList.end() || fontIter != m_fontList.end())
	{
		if (spriteIter != m_spriteList.end() && (fontIter == m_fontList.end() || spriteIter->first < fontIter->first))
		{
			//描画
			spriteIter->second->Draw(rc);
			spriteIter++;
		}
		else if(fontIter != m_fontList.end() && (spriteIter == m_spriteList.end() || fontIter->first < spriteIter->first))
		{
			fontIter->second->Draw(rc);
			fontIter++;
		}
		else 
		{
			//重なった時はフォントを優先して描画
			fontIter->second->Draw(rc);
			spriteIter->second->Draw(rc);
		}
	}

}