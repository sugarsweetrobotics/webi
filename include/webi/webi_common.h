#pragma once


/**
 * @brief DLLエクスポートの設定
 */
#ifdef _WINDOWS                         // Windows用の設定
#ifdef _USRDLL                        // DLL側コンパイルの場合
#define WEBI_API __declspec(dllexport)
#else                                 // ユーザ側コンパイルの設定
#ifdef _STATIC_EXPORTS               
#define WEBI_API                       // スタティックライブラリ用                  
#else
#define WEBI_API __declspec(dllimport) // ダイナミックリンク用
#endif 
#endif
#else 
#define WEBI_API                       // Linux用
#endif

#include <memory>

namespace webi {
  
  class Webi;
  using Webi_ptr = Webi*;

};
