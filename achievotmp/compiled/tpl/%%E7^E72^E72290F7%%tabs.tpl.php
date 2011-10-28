<?php /* Smarty version 2.6.11, created on 2011-10-27 18:00:25
         compiled from ./atk/themes/winxp/templates/tabs.tpl */ ?>
<script language="JavaScript" type="text/javascript">
var tabs = new Array();
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
?>tabs[tabs.length] = "<?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['tab']; ?>
"; <?php endfor; endif; ?>

var tabLeftImage = "<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_left_inactive.gif";
var tabRightImage = "<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_right_inactive.gif";
var tabBackgroundImage = "<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_back_inactive.gif";
var tabSelectedLeftImage = "<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_left_active.gif";
var tabSelectedRightImage = "<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_right_active.gif";
var tabSelectedBackgroundImage = "<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_back_active.gif";
var tabOverLeftImage = '<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_left_over.gif';
var tabOverBackgroundImage = '<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_back_over.gif';
var tabOverRightImage = '<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_right_over.gif';

var tabColor = "#FFFFFF";
var tabSelectedColor = "#FFFFFF";

<?php echo '
function mouseOverImage(el, left, right)
{
  el.style.backgroundImage = \'url(\' + tabOverBackgroundImage + \')\';
  document.getElementById(left).src = tabOverLeftImage;
  document.getElementById(right).src = tabOverRightImage;
}

function mouseOutImage(el, left, right)
{
  el.style.backgroundImage = \'url(\' + tabBackgroundImage + \')\';
  document.getElementById(left).src = tabLeftImage;
  document.getElementById(right).src = tabRightImage;
}

'; ?>


</script>

<table border="0" cellpadding="0" cellspacing="0" width="98%" align="center" valign="top">
  <tr>
    <td width="100%" bgcolor="#FFFFFF">
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
          <div style="position: relative;">
            <div id="tab_<?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['tab']; ?>
" style="position: absolute;">
            <table border="0" cellspacing="0" cellpadding="0">
                <tr>
                  <td><img  src="<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_left_active.gif"></td>
                  <td onclick="showTab('<?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['tab']; ?>
')" height="19" valign="middle" background="<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_back_active.gif" align="center" nowrap>
                    <?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['title']; ?>

                  </td>
                  <td><img src="<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_right_active.gif"></td>
                </tr>
              </table>
            </div>
            <table border="0" cellspacing="0" cellpadding="0" style="cursor: pointer;">
              <tr>
                <td><img id="left<?php echo $this->_sections['i']['index']; ?>
" src="<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_left_inactive.gif"></td>
                <td onclick="showTab('<?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['tab']; ?>
')" onmouseover="mouseOverImage(this, 'left<?php echo $this->_sections['i']['index']; ?>
', 'right<?php echo $this->_sections['i']['index']; ?>
');" onmouseout="mouseOutImage(this, 'left<?php echo $this->_sections['i']['index']; ?>
', 'right<?php echo $this->_sections['i']['index']; ?>
');" height="19" valign="middle" background="<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_back_inactive.gif" align="center" nowrap>
                    <?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['title']; ?>

                </td>
                <td><img id="right<?php echo $this->_sections['i']['index']; ?>
" src="<?php echo $this->_tpl_vars['themedir']; ?>
images/tab_right_inactive.gif"></td>
              </tr>
            </table>
          </div>
          </td>
          <?php endfor; endif; ?>
          <td valign="bottom" width="100%">
            <table cellspacing="0" cellpadding="0" border="0" width="100%">
              <tr><td bgcolor="#919B9C" height="1"><img src="<?php echo $this->_tpl_vars['themedir']; ?>
images/blank.gif" height="1" width="1"></td></tr>
            </table>
          </td>
        </tr>
      </table>
      <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td bgcolor="#919B9C" width="1"><img src="<?php echo $this->_tpl_vars['themedir']; ?>
images/blank.gif" width="1"></td>
          <td bgcolor="#FFFFFF" align="left" class="block">
            <table border="0" cellspacing="5" cellpadding="5" width="100%">
              <tr>
                <td>
                  <?php echo $this->_tpl_vars['content']; ?>

                </td>
              </tr>
            </table>
          </td>
          <td bgcolor="#919B9C" width="1"><img src="<?php echo $this->_tpl_vars['themedir']; ?>
images/blank.gif" width="1"></td>
        </tr>
        <tr height="1">
          <td bgcolor="#919B9C" colspan="3" valign="top"><img src="<?php echo $this->_tpl_vars['themedir']; ?>
images/blank.gif" height="1" width="1"></td>
        </tr>
      </table>
    </td>
  </tr>
</table>