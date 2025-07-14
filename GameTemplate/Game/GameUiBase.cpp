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

//位置更新
void GameUiBase::UpdateSpritePosition()
{
	//まずはスプライトの位置更新
	for (auto& sprite : m_spriteList)
	{
		//基底位置
		Vector2 basePos = m_basePosition;
		//＋座標
		Vector2 addPos = sprite.second.m_spritePosition;

		//更新位置
		Vector3 updatePos = Vector3::Zero;

		//更新後の位置を計算
		updatePos.x = basePos.x + addPos.x;
		updatePos.y = basePos.y + addPos.y;
		updatePos.z = 0.0f;

		//位置設定
		sprite.second.m_spritePtr->SetPosition(updatePos);
	}

	//次にフォントの位置更新
	for (auto& sprite : m_fontList)
	{
		//規定位置
		Vector2 basePos = m_basePosition;
		//＋座標
		Vector2 addPos = sprite.second.m_spritePosition;

		//更新位置
		Vector3 updatePos = Vector3::Zero;

		//更新後の位置を計算
		updatePos.x = basePos.x + addPos.x;
		updatePos.y = basePos.y + addPos.y;
		updatePos.z = 0.0f;

		//位置設定
		sprite.second.m_fontPtr->SetPosition(updatePos);
	}
}