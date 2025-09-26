/* 
PythonWindow.h

Suchen "class CMarkBox : public CWindow /> public:"

danach 	
		void SetScale(float fx, float fy);
		void SetOrigin(float fx, float fy);
		void SetRotation(float fRotation);
		void SetRenderingRect(float fLeft, float fTop, float fRight, float fBottom);
		void SetRenderingMode(int iMode);

hinzufügen : 
*/

#if defined(ENABLE_IMAGE_CLIP_RECT) || defined(ENABLE_BATTLE_PASS_SYSTEM)
		void SetImageClipRect(float fLeft, float fTop, float fRight, float fBottom, bool bIsVertical = false);
#endif
