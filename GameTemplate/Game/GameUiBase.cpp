#include "stdafx.h"
#include "GameUiBase.h"

//描画
void GameUiBase::DrawListSprites(RenderContext& rc)
{
	if (m_drawFlag == false)
	{
		return;
	}

	//スプライトリストのイテレーター
	auto spriteIter = m_spriteList.begin();
	//フォントリストのイテレーター
	auto fontIter = m_fontList.begin();

	while (spriteIter != m_spriteList.end() || fontIter != m_fontList.end())
	{
		//スプライトとフォントのどちらを描画するかを決定
		//描画順は番号で決定
		if (spriteIter != m_spriteList.end() && (fontIter == m_fontList.end() || spriteIter->first < fontIter->first))
		{
			//描画フラグがtrueであったら描画
			if (spriteIter->second.m_isDraw)
			{
				spriteIter->second.m_spritePtr->Draw(rc);
			}
			spriteIter++;
		}
		else if(fontIter != m_fontList.end() && (spriteIter == m_spriteList.end() || fontIter->first < spriteIter->first))
		{
			//描画フラグがtrueであったら描画
			if (fontIter->second.m_isDraw)
			{
				fontIter->second.m_fontPtr->Draw(rc);
			}
			fontIter++;
		}
		else 
		{
			//重なった時はフォントを優先して描画
			if (fontIter->second.m_isDraw)
			{
				fontIter->second.m_fontPtr->Draw(rc);
			}
			if (spriteIter->second.m_isDraw)
			{
				spriteIter->second.m_spritePtr->Draw(rc);
			}

			spriteIter++;
			fontIter++;
		}
	}

}
