<?php
// p2 -  �X���b�h�\�������̏����\��
// �t���[��3������ʁA�E������

include("./conf.php");  //��{�ݒ�t�@�C���Ǎ�

header_content_type();
if($doctype){ echo $doctype;}
echo <<<EOP
<html lang="ja">
<head>
	<meta name="ROBOTS" content="NOINDEX, NOFOLLOW">
	<meta http-equiv="Content-Style-Type" content="text/css">
	<meta http-equiv="Content-Script-Type" content="text/javascript">
	<title>p2</title>
EOP;

@include("./style/style_css.inc"); // ��{�X�^�C���V�[�g �Ǎ�

echo <<<EOP
</head>
<body>
<br>
<div class="container">
	<h1><img src="img/p2.gif" alt="p2" width="98" height="86"></h1>
</div>
</body>
</html>
EOP;

?>