#pragma once


/**
 * @brief DLL�G�N�X�|�[�g�̐ݒ�
 */
#ifdef _WINDOWS                         // Windows�p�̐ݒ�
#ifdef _USRDLL                        // DLL���R���p�C���̏ꍇ
#define WEBI_API __declspec(dllexport)
#else                                 // ���[�U���R���p�C���̐ݒ�
#ifdef _STATIC_EXPORTS               
#define WEBI_API                       // �X�^�e�B�b�N���C�u�����p                  
#else
#define WEBI_API __declspec(dllimport) // �_�C�i�~�b�N�����N�p
#endif 
#endif
#else 
#define WEBI_API                       // Linux�p
#endif

#include <memory>

namespace webi {
  
  class Webi;
  using Webi_ptr = Webi*;

};
