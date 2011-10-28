<?php /* Smarty version 2.6.11, created on 2011-10-27 18:00:24
         compiled from ./atk/themes/winxp/templates/recordlist.tpl */ ?>
<?php if (isset ( $this->_tpl_vars['formstart'] )):  echo $this->_tpl_vars['formstart'];  endif; ?>
<table border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td align="left">
        <table id="<?php echo $this->_tpl_vars['listid']; ?>
" class="recordlist" cellspacing=0>
            <!-- header -->
            <tr>
              <?php $_from = $this->_tpl_vars['header']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['col']):
?>
                <th valign="<?php echo $this->_tpl_vars['vorientation']; ?>
" <?php if (isset ( $this->_tpl_vars['col']['htmlattributes'] )):  echo $this->_tpl_vars['col']['htmlattributes'];  endif; ?>>
                  <?php if ($this->_tpl_vars['col']['content'] != ""):  echo $this->_tpl_vars['col']['content'];  else: ?>&nbsp;<?php endif; ?>
                </th>
              <?php endforeach; endif; unset($_from); ?>
            </tr>

            <?php if (count ( $this->_tpl_vars['sort'] )): ?>
              <!-- search row -->
              <tr>
              <?php echo $this->_tpl_vars['sortstart']; ?>

              <?php $_from = $this->_tpl_vars['sort']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['col']):
?>
                  <th valign="<?php echo $this->_tpl_vars['vorientation']; ?>
" <?php if (isset ( $this->_tpl_vars['col']['htmlattributes'] )):  echo $this->_tpl_vars['col']['htmlattributes'];  endif; ?> align="right">
                    <?php if ($this->_tpl_vars['col']['content'] != ""):  echo $this->_tpl_vars['col']['content'];  else: ?>&nbsp;<?php endif; ?>
                  </th>
              <?php endforeach; endif; unset($_from); ?>
              <?php echo $this->_tpl_vars['sortend']; ?>

              </tr>
            <?php endif; ?>

            <?php if (count ( $this->_tpl_vars['search'] )): ?>
              <!-- search row -->
              <tr>
              <?php echo $this->_tpl_vars['searchstart']; ?>

              <?php $_from = $this->_tpl_vars['search']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['col']):
?>
                  <th valign="<?php echo $this->_tpl_vars['vorientation']; ?>
" <?php if (isset ( $this->_tpl_vars['col']['htmlattributes'] )):  echo $this->_tpl_vars['col']['htmlattributes'];  endif; ?>>
                    <?php if ($this->_tpl_vars['col']['content'] != ""):  echo $this->_tpl_vars['col']['content'];  else: ?>&nbsp;<?php endif; ?>
                  </th>
              <?php endforeach; endif; unset($_from); ?>
              <?php echo $this->_tpl_vars['searchend']; ?>

              </tr>
            <?php endif; ?>

            <!-- records -->
            <?php echo $this->_tpl_vars['liststart']; ?>


            <?php $_from = $this->_tpl_vars['rows']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['row']):
?>
              <tr id="<?php echo $this->_tpl_vars['row']['id']; ?>
" class="row<?php if ($this->_tpl_vars['row']['rownum'] % 2 == 0): ?>1<?php else: ?>2<?php endif; ?>" <?php if ($this->_tpl_vars['row']['background'] != ""): ?>style="background-color:<?php echo $this->_tpl_vars['row']['background']; ?>
" <?php endif; ?>
                   onmouseover="highlightrow(this, '<?php echo $this->_tpl_vars['row']['highlight']; ?>
')"
                   onmouseout="resetrow(this)"
                   onclick="selectrow(this, '<?php echo $this->_tpl_vars['listid']; ?>
', <?php echo $this->_tpl_vars['row']['rownum']; ?>
)">
              <?php $_from = $this->_tpl_vars['row']['cols']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }$this->_foreach['i'] = array('total' => count($_from), 'iteration' => 0);
if ($this->_foreach['i']['total'] > 0):
    foreach ($_from as $this->_tpl_vars['col']):
        $this->_foreach['i']['iteration']++;
?>
                <<?php if ($this->_tpl_vars['row']['type'] == 'subtotal'): ?>th<?php else: ?>td<?php endif; ?> 
                  <?php if (($this->_foreach['i']['iteration']-1) > 0): ?>
                    onclick="rl_try('<?php echo $this->_tpl_vars['listid']; ?>
', event, <?php echo $this->_tpl_vars['row']['rownum']; ?>
, ['select', 'edit', 'view'], false);"<?php endif; ?> 
                  valign="<?php echo $this->_tpl_vars['vorientation']; ?>
" <?php if (isset ( $this->_tpl_vars['col']['htmlattributes'] )):  echo $this->_tpl_vars['col']['htmlattributes'];  endif; ?>>
                  <?php if ($this->_tpl_vars['col']['content'] != ""):  echo $this->_tpl_vars['col']['content'];  else: ?>&nbsp;<?php endif; ?>
                </td>
              <?php endforeach; endif; unset($_from); ?>
            </tr>
            <?php endforeach; endif; unset($_from); ?>

            <?php if (count ( $this->_tpl_vars['total'] )): ?>
            <!-- totals row -->
              <tr>
              <?php $_from = $this->_tpl_vars['total']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['col']):
?>
                  <th valign="<?php echo $this->_tpl_vars['vorientation']; ?>
" <?php if (isset ( $this->_tpl_vars['col']['htmlattributes'] )):  echo $this->_tpl_vars['col']['htmlattributes'];  endif; ?>>
                    <?php if ($this->_tpl_vars['col']['content'] != ""):  echo $this->_tpl_vars['col']['content'];  else: ?>&nbsp;<?php endif; ?>
                  </th>
              <?php endforeach; endif; unset($_from); ?>
              </tr>
            <?php endif; ?>

      </table>
    </td>
  </tr>
  <?php if ($this->_tpl_vars['mra'] != ""): ?>
  <!-- multirecord actions -->
   <tr>
     <td align="left">
       <table border="0" cellspacing="0" cellpadding="2">
         <tr>
           <td valign="top"><img src="<?php echo $this->_tpl_vars['atkroot']; ?>
atk/images/arrow.gif" border="0"></td>
           <td>
             <?php echo $this->_tpl_vars['mra']; ?>
 <?php echo $this->_tpl_vars['listend']; ?>

           </td>
         </tr>
       </table>
     </td>
   </tr>
  <?php endif; ?>
</table>
<?php if (isset ( $this->_tpl_vars['formend'] )):  echo $this->_tpl_vars['formend'];  endif; ?>