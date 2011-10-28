<?php /* Smarty version 2.6.11, created on 2011-10-27 18:00:19
         compiled from ./themes/default/templates/simplesearch.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'atktext', './themes/default/templates/simplesearch.tpl', 5, false),)), $this); ?>
<form action="<?php echo $this->_tpl_vars['dispatch']; ?>
"<?php if ($this->_tpl_vars['targetframe'] != ""): ?>target="<?php echo $this->_tpl_vars['targetframe']; ?>
"<?php endif; ?>>
<input type="hidden" name="atknodetype" value="search.search">
<input type="hidden" name="atkaction" value="search">
<?php echo $this->_tpl_vars['session_form']; ?>

<input name="searchstring" type="text" size="18" value="<?php echo $this->_tpl_vars['searchstring']; ?>
">&nbsp;<input type="submit" value="<?php echo smarty_function_atktext(array('0' => 'search'), $this);?>
">
</form>