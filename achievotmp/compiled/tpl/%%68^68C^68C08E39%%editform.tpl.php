<?php /* Smarty version 2.6.11, created on 2011-10-27 18:00:06
         compiled from ./atk/themes/achievo_modern/templates/editform.tpl */ ?>
  <?php $_from = $this->_tpl_vars['fields']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['field']):
?>
    <tr<?php if ($this->_tpl_vars['field']['rowid'] != ""): ?> id="<?php echo $this->_tpl_vars['field']['rowid']; ?>
"<?php endif;  if (! $this->_tpl_vars['field']['initial_on_tab']): ?> style="display: none"<?php endif; ?> class="<?php echo $this->_tpl_vars['field']['class']; ?>
">
      <?php if (isset ( $this->_tpl_vars['field']['line'] ) && $this->_tpl_vars['field']['line'] != ""): ?>
        <td colspan="2" valign="top" nowrap><?php echo $this->_tpl_vars['field']['line']; ?>
</td>
      <?php else: ?>
      <?php if ($this->_tpl_vars['field']['label'] !== 'AF_NO_LABEL'): ?><td valign="top" class="<?php if (isset ( $this->_tpl_vars['field']['error'] )): ?>errorlabel<?php else: ?>fieldlabel<?php endif; ?>"><?php if ($this->_tpl_vars['field']['label'] != ""): ?><b><?php echo $this->_tpl_vars['field']['label']; ?>
</b>:  <?php if (isset ( $this->_tpl_vars['field']['obligatory'] )):  echo $this->_tpl_vars['field']['obligatory'];  endif;  endif; ?></td><?php endif; ?>
<!--    </tr>
    <tr<?php if ($this->_tpl_vars['field']['rowid'] != ""): ?> id="<?php echo $this->_tpl_vars['field']['rowid']; ?>
"<?php endif;  if ($this->_tpl_vars['field']['initial_on_tab'] != 'yes'): ?> style="display: none"<?php endif; ?> class="<?php echo $this->_tpl_vars['field']['tab']; ?>
"> -->
        <td valign="top" id="<?php echo $this->_tpl_vars['field']['id']; ?>
" <?php if ($this->_tpl_vars['field']['label'] === 'AF_NO_LABEL'): ?>colspan="2"<?php endif; ?> class="field"><?php echo $this->_tpl_vars['field']['full']; ?>
</td>
      <?php endif; ?>
    </tr>
  <?php endforeach; endif; unset($_from); ?>