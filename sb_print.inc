<?php
// p2 �X���b�h�T�u�W�F�N�g�\���֐�
// for subject.php

//==================================================================
// sb_print - �X���b�h�ꗗ��\������֐� (<tr>�`</tr>)
//==================================================================
function sb_print($aThreadList)
{
	global $browser, $respointer, $subject_php, $_conf, $sb_view, $p2_setting, $STYLE;
	
	if (!$aThreadList->threads) {
		print "<tr><td>�@�Y���T�u�W�F�N�g�͂Ȃ�������</td></tr>";
		return;
	}
	
	// �ϐ� ================================================
	
	// >>1
	/*
	if (ereg("news", $aThreadList->bbs) || $aThreadList->bbs == "bizplus" || $aThreadList->spmode == "news") {
		// �q�ɂ͏���
		if ($aThreadList->spmode != "soko") {
			$only_one_bool = true;
		}
	}
	*/
	
	// �`�F�b�N�{�b�N�X
	if ($aThreadList->spmode == "taborn" or $aThreadList->spmode == "soko") {
		$checkbox_bool = true;
	}
	
	// ��
	if ($aThreadList->spmode and $aThreadList->spmode != "taborn" and $aThreadList->spmode != "soko") {
		$ita_name_bool = true;
	}

	$norefresh_q = "&amp;norefresh=true";

	// �\�[�g ==================================================
	
	// ���݂̃\�[�g�`����class�w���CSS�J���[�����O ======================
	$class_sort_midoku = "";	// �V��
	$class_sort_res = "";		// ���X
	$class_sort_no = "";		// No.
	$class_sort_title = "";		// �^�C�g��
	$class_sort_ita = "";		// ��
	$class_sort_spd = "";		// ���΂₳
	$class_sort_ikioi = "";		// ����
	$class_sort_bd = "";		// Birthday
	$class_sort_fav = "";		// ���C�ɓ���
	if ($p2_setting['sort']) {
		$nowsort_code = <<<EOP
\$class_sort_{$p2_setting['sort']}=' class="now_sort"';
EOP;
		eval($nowsort_code);
	}

	// �X�y�V�������[�h��
	if ($aThreadList->spmode) {
		$sortq_spmode = "&amp;spmode={$aThreadList->spmode}";
		// ���ځ[��Ȃ�
		if ($aThreadList->spmode == "taborn" or $aThreadList->spmode == "soko") {
			$sortq_host = "&amp;host={$aThreadList->host}";
			$sortq_ita = "&amp;bbs={$aThreadList->bbs}";
		}
	}else{
		$sortq_host = "&amp;host={$aThreadList->host}";
		$sortq_ita = "&amp;bbs={$aThreadList->bbs}";
	}
	
	$midoku_sort_ht = "<td class=\"tu\" nowrap><a{$class_sort_midoku} href=\"{$subject_php}?sort=midoku{$sortq_spmode}{$sortq_host}{$sortq_ita}{$norefresh_q}\" target=\"_self\">�V��</a></td>";

	//=====================================================
	// �e�[�u���w�b�_
	//=====================================================
	echo "<tr class=\"tableheader\">\n";
	
	// ����
	if ($sb_view == "edit") { echo "<td class=\"te\">&nbsp;</td>"; }
	// �V��
	if ($sb_view != "edit") { echo $midoku_sort_ht; }
	// ���X��
	if ($sb_view != "edit") {
		echo "<td class=\"tn\" nowrap><a{$class_sort_res} href=\"{$subject_php}?sort=res{$sortq_spmode}{$sortq_host}{$sortq_ita}{$norefresh_q}\" target=\"_self\">���X</a></td>";
	}
	// >>1
	if ($only_one_bool) { echo "<td class=\"t\">&nbsp;</td>"; }
	// �`�F�b�N�{�b�N�X
	if ($checkbox_bool) {
		echo "<td class=\"tc\"><input id=\"allbox\" name=\"allbox\" type=\"checkbox\" onClick=\"checkAll();\" title=\"���ׂĂ̍��ڂ�I���A�܂��͑I������\"></td>";
	}
	// No.
	echo "<td class=\"to\"><a{$class_sort_no} href=\"{$subject_php}?sort=no{$sortq_spmode}{$sortq_host}{$sortq_ita}{$norefresh_q}\" target=\"_self\">No.</a></td>";
	// �^�C�g��
	echo "<td class=\"tl\"><a{$class_sort_title} href=\"{$subject_php}?sort=title{$sortq_spmode}{$sortq_host}{$sortq_ita}{$norefresh_q}\" target=\"_self\">�^�C�g��</a></td>";
	// ��
	if ($ita_name_bool) {
		echo "<td class=\"t\"><a{$class_sort_ita} href=\"{$subject_php}?sort=ita{$sortq_spmode}{$sortq_host}{$sortq_ita}{$norefresh_q}\" target=\"_self\">��</a></td>";
	}
	// ���΂₳
	if ($_conf['sb_show_spd']) {
		echo "<td class=\"ts\"><a{$class_sort_spd} href=\"{$_conf['subject_php']}?sort=spd{$sortq_spmode}{$sortq_host}{$sortq_ita}{$norefresh_q}\" target=\"_self\">���΂₳</a></td>";
	}
	// ����
	echo "<td class=\"ti\"><a{$class_sort_ikioi} href=\"{$subject_php}?sort=ikioi{$sortq_spmode}{$sortq_host}{$sortq_ita}{$norefresh_q}\" target=\"_self\">����</a></td>";
	// Birthday
	echo "<td class=\"t\"><a{$class_sort_bd} href=\"{$subject_php}?sort=bd{$sortq_spmode}{$sortq_host}{$sortq_ita}{$norefresh_q}\" target=\"_self\">Birthday</a></td>";
	// ���C�ɓ���
	if ($_conf['sb_show_fav'] and $aThreadList->spmode != "taborn") {
		echo "<td class=\"t\"><a{$class_sort_fav} href=\"{$subject_php}?sort=fav{$sortq_spmode}{$sortq_host}{$sortq_ita}{$norefresh_q}\" target=\"_self\" title=\"���C�ɃX��\">��</a></td>";
	}
	
	echo "\n</tr>\n";

	//=====================================================
	//�e�[�u���{�f�B
	//=====================================================

	//spmode������΃N�G���[�ǉ�
	if ($aThreadList->spmode) {
		$spmode_q = "&amp;spmode={$aThreadList->spmode}";
	}

	$i = 0;
	foreach ($aThreadList->threads as $aThread) {
		$i++;
		$midoku_ari = "";
		$anum_ht = ""; // #r1
		
		$bbs_q = "&amp;bbs=".$aThread->bbs;
		$key_q = "&amp;key=".$aThread->key;

		if ($aThreadList->spmode != "taborn") {
			if (!$aThread->torder) { $aThread->torder = $i; }
		}

		// td�� css�N���X
		if (($i % 2) == 0) {
			$class_t = " class=\"t\"";		// ��{
			$class_te = " class=\"te\"";	// ���ёւ�
			$class_tu = " class=\"tu\"";	// �V�����X��
			$class_tn = " class=\"tn\"";	// ���X��
			$class_tc = " class=\"tc\"";	// �`�F�b�N�{�b�N�X
			$class_to = " class=\"to\"";	// �I�[�_�[�ԍ�
			$class_tl = " class=\"tl\"";	// �^�C�g��
			$class_ts = " class=\"ts\"";	// ���΂₳
			$class_ti = " class=\"ti\"";	// ����
		} else {
			$class_t = " class=\"t2\"";
			$class_te = " class=\"te2\"";
			$class_tu = " class=\"tu2\"";
			$class_tn = " class=\"tn2\"";
			$class_tc = " class=\"tc2\"";
			$class_to = " class=\"to2\"";
			$class_tl = " class=\"tl2\"";
			$class_ts = " class=\"ts2\"";
			$class_ti = " class=\"ti2\"";
		}
	
		//�V�����X�� =============================================
		$unum_ht_c = "&nbsp;";
		// �����ς�
		if ($aThread->isKitoku()) {
			$unum_ht_c = "<a class=\"un\" href=\"{$subject_php}?host={$aThread->host}{$bbs_q}{$key_q}{$spmode_q}&amp;dele=true\" target=\"_self\" onClick=\"return OpenSubWin('info.php?host={$aThread->host}{$bbs_q}{$key_q}&amp;popup=2&amp;dele=true',{$STYLE['info_pop_size']},0,0)\">{$aThread->unum}</a>";
		
			$anum = $aThread->rescount - $aThread->unum +1 -$respointer;
			if ($anum > $aThread->rescount) { $anum = $aThread->rescount; }
			$anum_ht = "#r".$anum;
			
			// �V������
			if ($aThread->unum > 0) {
				$midoku_ari = true;
				$unum_ht_c = "<a id=\"un{$i}\" class=\"un_a\" href=\"{$subject_php}?host={$aThread->host}{$bbs_q}{$key_q}{$spmode_q}&amp;dele=true\" target=\"_self\" onClick=\"return OpenSubWin('info.php?host={$aThread->host}{$bbs_q}{$key_q}&amp;popup=2&amp;dele=true',{$STYLE['info_pop_size']},0,0)\">$aThread->unum</a>";
			}
		
			// subject.txt�ɂȂ���
			if (!$aThread->isonline) {
				/*
				$unum_ht_c="<a class=\"un_n\" href=\"{$subject_php}?host={$aThread->host}{$bbs_q}{$key_q}{$spmode_q}&amp;dele=true\" target=\"_self\" onClick=\"return OpenSubWin('info.php?host={$aThread->host}{$bbs_q}{$key_q}&amp;dele=true',{$STYLE['info_pop_size']},0,0)\">-</a>";
				
				if($aThreadList->spmode == "soko" or $aThreadList->spmode == "palace" or $aThreadList->spmode == "fav"){
				*/
					// �듮��h�~�̂��߃��O�폜��������b�N
					$unum_ht_c = "<span class=\"un_n\">-</span>";
				/*
				}
				*/
				
			}	

		}
		
		$unum_ht = "<td{$class_tu}>".$unum_ht_c."</td>";
		
		// �����X�� =============================================
		$rescount_ht = "<td{$class_tn}>{$aThread->rescount}</td>";

		// �� ============================================
		if ($ita_name_bool) {
			$ita_name = $aThread->itaj ? $aThread->itaj : $aThread->bbs;
			$ita_ht = "<td{$class_t} nowrap><a href=\"{$subject_php}?host={$aThread->host}{$bbs_q}\" target=\"_self\">{$ita_name}</a></td>";
		}
		
		
		// ���C�ɓ��� ========================================
		if ($_conf['sb_show_fav']) {
			//if($aThread->fav){$favmark="��";}else{$favmark="+";}
			//if($aThread->fav){$favdo=0;}else{$favdo=1;}
			if ($aThreadList->spmode != "taborn") {
				if ($aThread->fav) {
					$fav_ht = "<td$class_t><a class=\"fav\" href=\"{$subject_php}?host={$aThread->host}{$bbs_q}{$key_q}{$spmode_q}{$norefresh_q}&amp;setfav=0\" target=\"_self\">��</a></td>";
				} else {
					$fav_ht = "<td{$class_t}><a class=\"fav\" href=\"{$subject_php}?host={$aThread->host}{$bbs_q}{$key_q}{$spmode_q}{$norefresh_q}&amp;setfav=1\" target=\"_self\">+</a></td>";
				}
			}
		}
		
		// torder(info) =================================================
		// ���C�ɃX��
		if ($aThread->fav) {
			$torder_st = "<b>{$aThread->torder}</b>";
		} else {
			$torder_st = $aThread->torder;
		}
		$torder_ht = "<a id=\"to{$i}\" class=\"info\" href=\"info.php?host={$aThread->host}{$bbs_q}{$key_q}\" target=\"_self\" onClick=\"return OpenSubWin('info.php?host={$aThread->host}{$bbs_q}{$key_q}&amp;popup=1',{$STYLE['info_pop_size']},0,0)\">{$torder_st}</a>";
		
		// title =================================================
		$chUnColor_ht = "";
		
		$rescount_q = "&amp;rc=".$aThread->rescount;
		
		// dat�q�� or �a���Ȃ�
		if ($aThreadList->spmode == "soko" || $aThreadList->spmode == "palace") { 
			$rescount_q = "";
			$offline_q = "&amp;offline=true";
			$anum_ht = "";
		}
		
		// �^�C�g�����擾�Ȃ�
		if (!$aThread->ttitle_ht) { 
			$aThread->ttitle_ht = "http://{$aThread->host}/test/read.cgi/{$aThread->bbs}/{$aThread->key}/";
		}
		
		// ���X��
		$moto_thre_ht = "";
		if (!$aThread->isKitoku()) {
			$moto_thre_ht = '<a class="thre_title" href="'.$aThread->getMotoThread('all').'">�E</a> ';
		}
		
		// �V�K�X��
		if ($aThread->new) { 
			$classtitle_q = " class=\"thre_title_new\"";
		} else {
			$classtitle_q = " class=\"thre_title\"";
		}
		
		$thre_url = "{$_conf['read_php']}?host={$aThread->host}{$bbs_q}{$key_q}{$rescount_q}{$offline_q}{$anum_ht}";
		
		
		if ($midoku_ari) {
			$chUnColor_ht = "chUnColor('{$i}');";
		}
		$change_color = " onClick=\"chTtColor('{$i}');{$chUnColor_ht}\"";
		
		// �I�����[>>1 =============================================
		if ($only_one_bool) {
			$one_ht = "<td{$class_t}><a href=\"{$_conf['read_php']}?host={$aThread->host}{$bbs_q}{$key_q}&amp;one=true\">&gt;&gt;1</a></td>";
		}
		
		// �`�F�b�N�{�b�N�X =============================================
		if ($checkbox_bool) {
			$checked_ht = "";
			if ($aThreadList->spmode == "taborn") {
				if (!$aThread->isonline) { $checked_ht=" checked"; } // or ($aThread->rescount >= 1000)
			}
			$checkbox_ht = "<td{$class_tc}><input name=\"checkedkeys[]\" type=\"checkbox\" value=\"{$aThread->key}\"$checked_ht></td>";
		}
		
		// ���� =============================================
		if ($sb_view == "edit") {
			$unum_ht = "";
			$rescount_ht = "";
			$sb_view_q = "&amp;sb_view=edit";
			if ($aThreadList->spmode == "fav") {
				$setkey = "setfav";
			} elseif ($aThreadList->spmode == "palace") {
				$setkey = "setpal";
			}
			$narabikae_a = "{$subject_php}?host={$aThread->host}{$bbs_q}{$key_q}{$spmode_q}{$sb_view_q}";
			
			$edit_ht = <<<EOP
		<td{$class_te}>
			<a class="te" href="{$narabikae_a}&amp;{$setkey}=top" target="_self">��</a>
			<a class="te" href="{$narabikae_a}&amp;{$setkey}=up" target="_self">��</a>
			<a class="te" href="{$narabikae_a}&amp;{$setkey}=down" target="_self">��</a>
			<a class="te" href="{$narabikae_a}&amp;{$setkey}=bottom" target="_self">��</a>
		</td>
EOP;
		}
		
		// ���΂₳�i�� ����/���X �� ���X�Ԋu�j
		$spd_ht = "";
		if ($_conf['sb_show_spd']) {
			if ($spd_st = $aThread->getTimePerRes()) {
				$spd_ht = "<td{$class_ts}>{$spd_st}</td>";
			}		
		}
		
		// ����
		if ($aThread->dayres > 0) {
			$dayres_st = sprintf("%01.2f", $aThread->dayres);
		} else {
			$dayres_st = "-";
		}
		$ikioi_ht = "<td{$class_ti}>".$dayres_st."</td>";
		
		// Birthday
		$birthday = date("y/m/d", $aThread->key); // (y/m/d H:i)
		$birth_ht = "<td{$class_t}>{$birthday}</td>";

		//====================================================================================
		// �X���b�h�ꗗ table �{�f�B HTML�v�����g <tr></tr> 
		//====================================================================================

		// �{�f�B
		echo "<tr>\n
					$edit_ht
					$unum_ht
					$rescount_ht
					$one_ht
					$checkbox_ht
					<td{$class_to}>{$torder_ht}</td>
					<td{$class_tl} nowrap>$moto_thre_ht<a id=\"tt{$i}\" href=\"{$thre_url}\"{$classtitle_q}{$change_color}>{$aThread->ttitle_ht}</a></td>
					$ita_ht
					$spd_ht
					$ikioi_ht
					$birth_ht
					$fav_ht
				\n</tr>\n";

	}

}

?>