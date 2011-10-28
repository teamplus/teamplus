<?php /* Smarty version 2.6.11, created on 2011-10-27 18:00:19
         compiled from ./atk/themes/modern/templates/tabs.tpl */ ?>
<br><table border="0" cellpadding="0" cellspacing="0" bgcolor="#606060" width="100%" align="center" valign="top">
  <tr>
    <td width="100%" bgcolor="#D8E4F0">
      <table border="0" cellpadding="0" cellspacing="0">
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

          <td valign="bottom">
            <table cellspacing="0" cellpadding="5" id="tab_<?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['tab']; ?>
" class="<?php if ($this->_tpl_vars['tabs'][$this->_sections['i']['index']]['selected']): ?>activetab<?php else: ?>passivetab<?php endif; ?>">
              <tr>
                <td onclick="showTab('<?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['tab']; ?>
')" nowrap>
                    <b><?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['title']; ?>
</b>
                </td>
              </tr>
            </table>
          </td>

          <?php endfor; endif; ?>
          <td valign="bottom" width="100%">
            <table cellspacing="0" cellpadding="0" border="0" width="100%">
              <tr><td bgcolor="#000000" height="1"><img src="<?php echo $this->_tpl_vars['themedir']; ?>
images/blank.gif" height="1" width="1"></td></tr>
            </table>
          </td>
        </tr>
      </table>
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td bgcolor="#000000" width="1"><img src="<?php echo $this->_tpl_vars['themedir']; ?>
images/blank.gif" width="1"></td>
          <td bgcolor="#E0E5F7" align="left" class="block">
            <table border="0" cellspacing="5" cellpadding="5" width="100%">
              <tr>
                <td>
                  <?php echo $this->_tpl_vars['content']; ?>

                </td>
              </tr>
            </table>
          </td>
          <td bgcolor="#000000" width="1"><img src="<?php echo $this->_tpl_vars['themedir']; ?>
images/blank.gif" width="1"></td>
        </tr>
        <tr>
          <td bgcolor="#000000" colspan="3" valign="top"><img src="<?php echo $this->_tpl_vars['themedir']; ?>
images/blank.gif" height="1" width="1"></td>
        </tr>
      </table>
    </td>
  </tr>
</table>