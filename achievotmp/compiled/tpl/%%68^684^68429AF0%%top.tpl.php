<?php /* Smarty version 2.6.11, created on 2011-10-27 18:01:18
         compiled from ./atk/themes/basic/templates/top.tpl */ ?>
<div id="atktop">
<h1><?php echo $this->_tpl_vars['title']; ?>
</h1>
<span id="atktopleft">
  <span id="atkloggedinas"><?php echo $this->_tpl_vars['logintext']; ?>
: </span>
  <span id="atkloggedinuser"><?php echo $this->_tpl_vars['user']; ?>
</span>
  <a id="atklogoutlink" href="<?php echo $this->_tpl_vars['logoutlink']; ?>
" target="<?php echo $this->_tpl_vars['logouttarget']; ?>
"><?php echo $this->_tpl_vars['logouttext']; ?>
</a>
</span>
<?php if ($this->_tpl_vars['centerpiece'] != ""): ?>
  <span id="atktopcenter"><?php echo $this->_tpl_vars['centerpiece']; ?>
</span>
<?php endif;  if ($this->_tpl_vars['searchpiece'] != ""): ?>
  <span id="atktopsearch"><?php echo $this->_tpl_vars['searchpiece']; ?>
</span>
<?php endif; ?>
</div>