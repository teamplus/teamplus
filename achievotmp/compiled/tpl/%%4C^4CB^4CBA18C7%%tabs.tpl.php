<?php /* Smarty version 2.6.11, created on 2011-10-27 18:00:54
         compiled from ./atk/themes/default/templates/tabs.tpl */ ?>
<table border="0" cellpadding="0" cellspacing="0" width="98%" align="center" valign="top">
  <tr>
    <td width="100%">
      <table border="1" cellpadding="2" cellspacing="0">
        <tr>                              
          <?php unset($this->_sections['i']);
$this->_sections['i']['name'] = 'i';
$this->_sections['i']['loop'] = is_array($_loop=$this->_tpl_vars['tabs']) ? count($_loop) : max(0, (int)$_loop); unset($_loop);
$this->_sections['i']['show'] = true;
$this->_sections['i']['max'] = $this->_sections['i']['loop'];
$this->_sections['i']['step'] = 1;
$this->_sections['i']['start'] = $this->_sections['i']['step'] > 0 ? 0 : $this->_sections['i']['loop']-1;
if ($this->_sections['i']['show']) {
    $this->_sections['i']['total'] = $this->_sections['i']['loop'];
    if ($this->_sections['i']['total'] == 0)
        $this->_sections['i']['show'] = false;
} else
    $this->_sections['i']['total'] = 0;
if ($this->_sections['i']['show']):

            for ($this->_sections['i']['index'] = $this->_sections['i']['start'], $this->_sections['i']['iteration'] = 1;
                 $this->_sections['i']['iteration'] <= $this->_sections['i']['total'];
                 $this->_sections['i']['index'] += $this->_sections['i']['step'], $this->_sections['i']['iteration']++):
$this->_sections['i']['rownum'] = $this->_sections['i']['iteration'];
$this->_sections['i']['index_prev'] = $this->_sections['i']['index'] - $this->_sections['i']['step'];
$this->_sections['i']['index_next'] = $this->_sections['i']['index'] + $this->_sections['i']['step'];
$this->_sections['i']['first']      = ($this->_sections['i']['iteration'] == 1);
$this->_sections['i']['last']       = ($this->_sections['i']['iteration'] == $this->_sections['i']['total']);
?>
          <td valign="middle" align="left" nowrap>
          <?php if ($this->_tpl_vars['tabs'][$this->_sections['i']['index']]['selected']): ?>
            <b>&nbsp;<?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['title']; ?>
&nbsp;</b>
          <?php else: ?>
            &nbsp;<a href="<?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['link']; ?>
" style="color:black;text-decoration:none"><?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['title']; ?>
</a>&nbsp;
          <?php endif; ?>
          </td>          
          <?php endfor; endif; ?>
        </tr>
      </table>
      <table border="1" cellspacing="0" cellpadding="5" width="100%">
        <tr>
          <td>
            <?php echo $this->_tpl_vars['content']; ?>

          </td>
        </tr>
      </table>
    </td>
  </tr>
</table>