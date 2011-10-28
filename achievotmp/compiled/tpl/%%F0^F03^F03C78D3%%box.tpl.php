<?php /* Smarty version 2.6.11, created on 2011-10-27 18:00:06
         compiled from ./atk/themes/achievo_modern/templates/box.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'atkthemeimg', './atk/themes/achievo_modern/templates/box.tpl', 2, false),)), $this); ?>
<div id="box-content">
<div class="tableHeader"><span class="tableHeaderTitle"><?php echo $this->_tpl_vars['title']; ?>
 <span style="visibility: hidden" id="atkbusy"><img src="<?php echo smarty_function_atkthemeimg(array('0' => "spinner.gif"), $this);?>
" /></span></span><img src="<?php echo smarty_function_atkthemeimg(array('0' => "tabRight.gif"), $this);?>
" alt="tabend"></div>
<div class="contentBlock"><?php echo $this->_tpl_vars['content']; ?>
</div>
</div>