<?php
// p2 - �{�[�h���j���[��\������ �N���X

class ShowBrdMenuPc{
	var $cate_id; //�J�e�S���[ID
	
	function ShowBrdMenuPc(){
		$this->cate_id = 1;
	}
	
	//=========================================================
	//���j���[���v�����g���郁�\�b�h
	//=========================================================
	function printBrdMenu($categories){
		global $subject_php, $_info_msg_ht;
		global $k_sb_disp_range;

		if($categories){
			foreach($categories as $cate){
				if($cate->num > 0){
					echo "<div class=\"menu_cate\">\n";
					echo "	<b><a class=\"menu_cate\" href=\"javascript:void(0);\" onClick=\"showHide('c{$this->cate_id}');\">{$cate->name}</a></b>\n";
					if($cate->is_open or $cate->match_attayo){
						echo "	<div class=\"itas\" id=\"c{$this->cate_id}\">\n";
					}else{
						echo "	<div class=\"itas_hide\" id=\"c{$this->cate_id}\">\n";
					}
					foreach($cate->menuitas as $mita){
						echo "		<a href=\"{$_SERVER['PHP_SELF']}?host={$mita->host}&amp;bbs={$mita->bbs}&amp;itaj_en={$mita->itaj_en}&amp;setfavita=1\" target=\"_self\" class=\"fav\">+</a> <a href=\"{$subject_php}?host={$mita->host}&amp;bbs={$mita->bbs}&amp;itaj_en={$mita->itaj_en}\">{$mita->itaj_ht}</a><br>\n";
					}
					echo "	</div>\n";
					echo "</div>\n";
				}
				$this->cate_id++;
			}
		}
		
	}
	
	//=========================================================
	// ���C�ɔ��v�����g����
	//=========================================================
	function print_favIta()
	{
		global $_conf, $favita_path, $subject_php, $matome_i, $STYLE, $c_enable_menu_new;
		
		$lines= @file($favita_path); // favita�ǂݍ���
		
		if($lines){
		echo <<<EOP
	<div class="menu_cate"><b><a class="menu_cate" href="javascript:void(0);" onClick="showHide('c_favita');">���C�ɔ�</a></b> [<a href="editfavita.php" target="subject">�ҏW</a>]<br>
		<div class="itas" id="c_favita">
EOP;
			foreach($lines as $l){
				$l = rtrim($l);
				if( preg_match("/^\t?(.+)\t(.+)\t(.+)$/", $l, $matches) ){
					$itaj = rtrim($matches[3]);
					$itaj_en = base64_encode($itaj);
					
					if($c_enable_menu_new && $_GET['new']){	// �V������\������ꍇ
						$matome_i++;
						$host = $matches[1];
						$bbs = $matches[2];
						$spmode = "";
						$shinchaku_num = 0;
						$_newthre_num = 0;
						$newthre_ht = "";
						include("./subject_new.php");	// $shinchaku_num, $_newthre_num ���Z�b�g
						if($shinchaku_num>0){
							$class_newres_num = " class=\"newres_num\"";
						}else{
							$class_newres_num = " class=\"newres_num_zero\"";
						}
						if($_newthre_num){
							$newthre_ht = "{$_newthre_num}";
						}
						echo <<<EOP
				<a href="{$_SERVER['PHP_SELF']}?host={$matches[1]}&amp;bbs={$matches[2]}&amp;setfavita=0" target="_self" class="fav">��</a>
				<a href="{$subject_php}?host={$matches[1]}&amp;bbs={$matches[2]}&amp;itaj_en={$itaj_en}" onClick="chMenuColor({$matome_i});">{$matches[3]}</a> <span id="newthre{$matome_i}" class="newthre_num">{$newthre_ht}</span> (<a href="{$_conf['read_new_php']}?host={$matches[1]}&amp;bbs={$matches[2]}" target="read" id="un{$matome_i}" onClick="chUnColor({$matome_i});"{$class_newres_num}>{$shinchaku_num}</a>)<br>
EOP;

					}else{	// �V������\�����Ȃ��ꍇ
						echo <<<EOP
				<a href="{$_SERVER['PHP_SELF']}?host={$matches[1]}&amp;bbs={$matches[2]}&amp;setfavita=0" target="_self" class="fav">��</a>
				<a href="{$subject_php}?host={$matches[1]}&amp;bbs={$matches[2]}&amp;itaj_en={$itaj_en}">{$matches[3]}</a><br>
EOP;

				
					}

				}
			}
			
			echo "	</div>\n";
			echo "</div>\n";
			
		}else{//����ۂȂ�
			echo <<<EOP
	<div class="menu_cate"><b>���C�ɔ�</b> [<a href="editfavita.php" target="subject">�ҏW</a>]<br>
		<div class="itas" id="c_favita">
			�@�i����ہj
		</div>
	</div>
EOP;
		}
		
	}
	
}
?>