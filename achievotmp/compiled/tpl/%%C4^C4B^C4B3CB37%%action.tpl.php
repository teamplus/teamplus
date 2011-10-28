<?php /* Smarty version 2.6.11, created on 2011-10-27 18:01:18
         compiled from ./atk/themes/basic/templates/action.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'atkmessages', './atk/themes/basic/templates/action.tpl', 3, false),)), $this); ?>
<?php echo $this->_tpl_vars['formstart']; ?>

  <?php if (isset ( $this->_tpl_vars['helplink'] )): ?><div id="atkhelp"><?php echo $this->_tpl_vars['helplink']; ?>
</div><?php endif; ?>
  <?php echo smarty_function_atkmessages(array(), $this);?>

  <?php if (count ( $this->_tpl_vars['atkmessages'] )): ?>
  <div class="atkmessages">
    <?php $_from = $this->_tpl_vars['atkmessages']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['message']):
?>
      <div class="atkmessages_<?php echo $this->_tpl_vars['message']['type']; ?>
"><?php echo $this->_tpl_vars['message']['message']; ?>
</div>
    <?php endforeach; endif; unset($_from); ?>
  </div>
  <?php endif; ?>
  <div id="atkcontent">
    <?php echo $this->_tpl_vars['content']; ?>

  </div>
  <div id="atkbuttons">
    <?php $_from = $this->_tpl_vars['buttons']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['button']):
?>
      <span class="atkbutton"><?php echo $this->_tpl_vars['button']; ?>
</span>
    <?php endforeach; endif; unset($_from); ?>
  </div>
<?php echo $this->_tpl_vars['formend']; ?>
