<?php
/* p2 - �܂�BBS�p�̊֐��i�� JBBS@������΁j*/

require_once("./filectl_class.inc");
require_once './p2util.class.php';	// p2�p�̃��[�e�B���e�B�N���X

//=====================================================
// �܂�BBS��read.pl ��ǂ�� dat�ɕۑ�����֐�
//=====================================================
function machiDownload(){
	global $aThread, $machi_latest_num;

	$machi_latest_num="";
	
	//����dat�̎擾���X�����K�����ǂ�����O�̂��߃`�F�b�N
	if(file_exists($aThread->keydat)){
		$dls=@file($aThread->keydat);
		if( sizeof($dls) != $aThread->rnum){
			//echo "bad size!<br>";
			unlink($aThread->keydat);
			$aThread->rnum=0;
		}
	}
	
	if($aThread->rnum==""){$aThread->rnum=0;}
	if($aThread->rnum==0){
		$mode="w";
		$zero_read=true;
	}else{
		$mode="a";
	}

	if($zero_read){
		$START=1;
	}else{
		$START=$aThread->rnum+1;
	}
	
	//JBBS@�������
	if (P2Util::isHostJbbsShitaraba($aThread->host)) { 
		$read_cgi="read.cgi";
	//�܂�BBS
	} else { 
		$read_cgi="read.pl";
	}
	
	// ������΂�livedoor�ړ]�ɑΉ��B�Ǎ����livedoor�Ƃ���B
	$host = P2Util::adjustHostJbbs($aThread->host);
	
	$machiurl="http://{$aThread->host}/bbs/{$read_cgi}?BBS={$aThread->bbs}&KEY={$aThread->key}&START={$START}";

	$tempfile=$aThread->keydat.".html.temp";
	FileCtl::mkdir_for($tempfile);
	
	$machiurl_res = fileDownload($machiurl, $tempfile);
	
	if( $machiurl_res->is_error() ){
		$aThread->diedat=true;
		return false;
	}
	
	// ������΂Ȃ�EUC��SJIS�ɕϊ�
	if (P2Util::isHostJbbsShitaraba($aThread->host)) { 
	
		$temp_data = FileCtl::get_file_contents($tempfile);
		
		include_once("./strctl_class.inc");
		$temp_data = StrCtl::p2EUCtoSJIS($temp_data);
		$fp = @fopen($tempfile,"w") or die("Error: $tempfile ���X�V�ł��܂���ł���");
		fputs($fp, $temp_data);
		fclose($fp);
	}
	
	$mlines=@file($tempfile);
	if(file_exists($tempfile)){unlink($tempfile);}
	
	if($mlines[1]=="<html>error</html>\r\n"){
		$aThread->diedat=true;
		return false;
	}
	
	$mdatlines = machiHtmltoDatLines($mlines);

	//��������=====================================
	$fp = @fopen($aThread->keydat, $mode) or die("Error: $aThread->keydat ���X�V�ł��܂���ł���");
	for($i=$START; $i<=$machi_latest_num; $i++){
		if($mdatlines[$i]){
			fputs($fp, $mdatlines[$i]);
		}else{
			fputs($fp, "���ځ[��<>���ځ[��<>���ځ[��<>���ځ[��<>\n");
		}
	}
	fclose($fp);
	
	$aThread->isonline=true;
	return true;
}


//=====================================================
//  �܂�BBS��read.pl�œǂݍ���HTML��dat�ɕϊ�����֐�
//=====================================================
function machiHtmltoDatLines($mlines){
	global $machi_latest_num;

	if(!$mlines){return false;}
	$mdatlines="";
	
	foreach($mlines as $ml){
		$ml = rtrim($ml);
		if(!$tuduku){unset($order,$mail ,$name ,$date, $ip ,$body);}

		if($tuduku){
			if(preg_match("/^ \]<\/font><br><dd>(.*) <br><br>$/i", $ml, $matches)){
				$body=$matches[1];
			}else{
				unset($tuduku);
				continue;
			}
		}elseif(preg_match("/^<dt>(\d+) ���O�F(<font color=\"#.+?\">|<a href=\"mailto:(.*)\">)<b> (.+) <\/b>(<\/font>|<\/a>) ���e���F (.+)<br><dd>(.*) <br><br>$/i", $ml, $matches)){
			$order= $matches[1];
			$mail= $matches[3];
			$name= preg_replace("/<font color=\"?#.+?\"?>(.+)<\/font>/i", "\\1", $matches[4]);
			$date= $matches[6];
			$body= $matches[7];
		}elseif(preg_match("/<title>(.*)<\/title>/i", $ml, $matches)){
			$mtitle=$matches[1];
			continue;
		}elseif(preg_match("/^<dt>(\d+) ���O�F(<font color=\"#.+?\">|<a href=\"mailto:(.*)\">)<b> (.+) <\/b>(<\/font>|<\/a>) ���e���F (.+) <font size=1>\[ (.+)$/i", $ml, $matches)){
			$order= $matches[1];
			$mail= $matches[3];
			$name= preg_replace("/<font color=\"?#.+?\"?>(.+)<\/font>/i", "\\1", $matches[4]);
			$date= $matches[6];
			$ip= $matches[7];
			$tuduku=true;
			continue;
		}
		
		if ($ip) {
			$date = "$date [$ip]";
		}

		// �������JBBS jbbs.livedoor.com ��link.cgi������
		// <a href="http://jbbs.livedoor.jp/bbs/link.cgi?url=http://dempa.2ch.net/gazo/free/img-box/img20030424164949.gif" target="_blank">http://dempa.2ch.net/gazo/free/img-box/img20030424164949.gif</a>
		$body = preg_replace("{<a href=\"http://(jbbs\.livedoor\.jp|jbbs\.livedoor\.com|jbbs\.shitaraba\.com)/bbs/link\.cgi\?url=([^\"]+)\" target=\"_blank\">([^><]+)</a>}i","\\2", $body);
		
		// �����N�O��
		$body = preg_replace("/<a href=\"(https?:\/\/[-_.!~*'()a-zA-Z0-9;\/?:@&=+\$,%#]+)\" target=\"_blank\">(https?:\/\/[-_.!~*'()a-zA-Z0-9;\/?:@&=+\$,%#]+)<\/a>/i","\\1", $body); //�����N�O��
		
		if($order==1){
			$datline = $name."<>".$mail."<>".$date."<>".$body."<>".$mtitle."\n";
		}else{
			$datline = $name."<>".$mail."<>".$date."<>".$body."<>\n";
		}
		$mdatlines[$order]=$datline;
		if($order > $machi_latest_num){$machi_latest_num = $order;}
		unset($tuduku);
	}
	
	return $mdatlines;
}

?>