<?php /* Smarty version 2.6.11, created on 2011-10-27 18:00:19
         compiled from ./atk/themes/default/templates/action.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'atkmessages', './atk/themes/default/templates/action.tpl', 5, false),)), $this); ?>
<?php echo $this->_tpl_vars['formstart']; ?>

<table border="0" cellspacing="0" cellpadding="2" width="100%">
  <?php if (isset ( $this->_tpl_vars['helplink'] )): ?><tr><td align="right" class="helplink"><?php echo $this->_tpl_vars['helplink']; ?>
</td></tr><?php endif; ?>
  
  <?php echo smarty_function_atkmessages(array(), $this);?>

  <?php if (count ( $this->_tpl_vars['atkmessages'] )): ?>
    <tr>
      <td align="center" valign="top">
        <br>  
        <div class="atkmessages">
          <?php $_from = $this->_tpl_vars['atkmessages']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['message']):
?>
            <div class="atkmessages_<?php echo $this->_tpl_vars['message']['type']; ?>
"><?php echo $this->_tpl_vars['message']['message']; ?>
</div>
          <?php endforeach; endif; unset($_from); ?>
        </div>
        </div>
      </td
    </tr>        
  <?php endif; ?>  
  
  <?php if (( isset ( $this->_tpl_vars['header'] ) && ! empty ( $this->_tpl_vars['header'] ) )): ?>
  <tr>
    <td valign="top" align="left"><?php echo $this->_tpl_vars['header']; ?>
<br><br></td>
  </tr>
  <?php endif; ?>
  <tr>
    <td valign="top" align="center"><?php echo $this->_tpl_vars['content']; ?>
<br></td>
  </tr>
  <tr>
    <td align="center" valign="top">
      <?php $_from = $this->_tpl_vars['buttons']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['button']):
?>
        &nbsp;<?php echo $this->_tpl_vars['button']; ?>
&nbsp;
      <?php endforeach; endif; unset($_from); ?><br><br></td>
  </tr>
</table>
<?php echo $this->_tpl_vars['formend']; ?>
