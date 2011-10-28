<?php

  /**
   * Add a selected events to the session variable.
   * If the session variable is empty, it is filled with
   * the eventss the user has recently booked on.
   */

  global $g_eventsnamesize; // must declare global. this piece of code might
                             // be executed somewhere in a local function scope.
  $g_eventsnamesize = 20;

  /**
   * Return the Achievo version number.
   * @return string the version number of Achievo
   */
  function achievoVersion()
  {
    require(atkconfig("atkroot")."version.inc");
    return $achievo_version;
  }

  /**
   * Return the Achievo state. (stable or development)
   * @return string the state of Achievo
   */
  function achievoState()
  {
    require(atkconfig("atkroot")."version.inc");
    return $achievo_state;
  }

  function getAchievoTitle()
  {
    $achievo_version = achievoVersion();
    $achievo_state = achievoState();
    $title = atktext("app_title")." ".$achievo_version;
    if($achievo_state!=="stable") $title.=" ($achievo_state)";
    return $title;
  }

  function getSearchPiece()
  {
    $theme = &atkinstance("atk.ui.atktheme");
    if($theme->getAttribute('useframes',true)) { $target='main'; } else { $target=""; }
    $node = atkconfig("top_search_node") ? atkconfig("top_search_node") : "search.search";
    $searchnode = &atkGetNode($node);
    $searchpiece = $searchnode->simpleSearchForm("", $target, SESSION_NEW);
    return $searchpiece;
  }

  function getCenterPiece(&$centerpiece,&$centerpiecelinks)
  {
    $user = &atkGetUser();
    if ($user["name"]!="administrator")
    {
      $theme = &atkinstance("atk.ui.atktheme");

      // Set the dispatchfile for this menu based on the theme setting, or to the default if not set.
      // This makes sure that all calls to dispatch_url will generate a url for the main frame and not
      // within the menu itself.
      $dispatcher = $theme->getAttribute('dispatcher', atkconfig("dispatcher", "dispatch.php")); // do not use atkSelf here!
      $c = &atkinstance("atk.atkcontroller");
      $c->setPhpFile($dispatcher);

      if($theme->getAttribute('useframes',true)) { $target='target="main"'; } else { $target=""; }
      $centerpiece = $centerpiecelinks['pim'] = href(dispatch_url("pim.pim", "pim"), atktext("pim"), SESSION_NEW, false,$target);
      if (is_allowed("employee.userprefs", "edit"))
      {
        $centerpiece.= '&nbsp; &nbsp; &nbsp;';
        $centerpiece.= $centerpiecelinks['userprefs'] = href(dispatch_url("employee.userprefs", "edit", array("atkselector" => "person.id='".$user["id"]."'")), atktext("userprefs"), SESSION_NEW, false,$target);
      }
    }
    else
    {
      // Administrator has a link to setup.php
      $centerpiece = $centerpiecelinks['setup'] = href("setup.php", atktext("setup"), SESSION_NEW, false, 'target="_top"');
    }
  }

  function getFullUsername()
  {
    $user = &atkGetUser();
    $username = "<b>".$user["name"]."</b>";
    if($user["name"]!="administrator") $username.=" [".$user["firstname"]." ".$user["lastname"]."]";
    atkdebug("achievotools::getFullUsername() -> ".$username);
    return $username;
  }


  function updateSelectedProjects()
  {
    global $g_sessionManager, $g_eventsnamesize;

    atkdebug("updateSelectedProject");
    $prj = array();
    //Get current sessionvar
    $session = &atkSessionManager::getSession();
    $prj =  $g_sessionManager->getValue("selectedprj","globals");

    //If session var is empty fill with recent eventss
    if (count($prj) == 0)
    {
      $prj = getRecentProjects();
    }

    //Delete atkselector from global vars, because the stackVar
    //function overwrites the stack val of atkselector
    //when it finds a value in $GLOBALS
    //$_REQUEST['atkselector'] = "";

 //Check if selected events already exists in session var
    $atkselect = $g_sessionManager->stackVar("atkselector");

    if (($atkselect != "") && isset($atkselect))
    {
       $eventsid = sscanf($atkselect, "events.id='%d'");
       $prjId = $eventsid[0];
    }
    else
    {
        $atkselect = $g_sessionManager->stackVar("selectedeventsid");
        if (($atkselect != "") && isset($atkselect))
        {
          $prjId = $atkselect;
        }
        else
        {
          $prjId = 0;
        }
    }

    // When no events is selected in the dropdown list
    // and the user select's a events we need to check
    // if the events is in the list. If not
    // we need to get it's name, so it can be displayed
    // in the dropdown list
    if ($prjId != 0)
    {
       $found = FALSE;
       foreach( $prj as $cur)
       {
         if ($cur['eventsid']  == $prjId) $found = TRUE;
       }
       if (!$found)  //add events to dropdown list
       {

         $selectedPrj = Array();
         $selectedPrj['eventsid'] = $prjId;

         //Get events name
         $db = &atkGetDb();
         $query = "SELECT events.abbreviation as eventscode, events.name as eventsname FROM events WHERE id='".$selectedPrj['eventsid']."'";
         $arr = $db->getrows($query);
         $eventsdescriptor = empty($arr[0]['eventscode']) ? $arr[0]['eventsname'] : ($arr[0]['eventscode'] . ": " . $arr[0]['eventsname']);
         if (atk_strlen($eventsdescriptor) > $g_eventsnamesize)
         {
           $selectedPrj['eventsname'] = atk_substr($eventsdescriptor, 0, $g_eventsnamesize-2).".."; //update because of phases
         }
         else
         {
           $selectedPrj['eventsname'] = $eventsdescriptor; //update because of phases
         }

         //Check maximum number of eventss in session var
         if (count($prj) >= atkconfig("numberofrecenteventss"))
         {
           array_shift($prj); // remove the first
           $prj[count($prj)-1] = $selectedPrj;
         }
         else
         {
           $prj[] = $selectedPrj;
         }

       }

       //Reload the menu frame by creating javascript
       $menu_url = session_url("menu.php?atkmenutop=eventsmanagement&selectedevents=".$prjId, SESSION_DEFAULT);
       $script = "var newlocation=\"$menu_url\";
                  var oldlocation=parent.menu.location.toString();
                  if (oldlocation.indexOf(newlocation) == -1) {parent.menu.location = newlocation;}";
       $page = &atkinstance("atk.ui.atkpage");
       $page->register_loadScript($script);
     }

     // Copy prj to session var
     // Use global session because menu.php uses
     // a different namespace
     $g_sessionManager->globalVar("selectedprj", $prj, true);
  }

  /**
   * Get the eventss the user recently booked hours on
   * @return array with recently used eventss
   */
  function getRecentProjects()
  {
    global $g_eventsnamesize;
    $db = &atkGetDb();

    $userid = atkArrayNvl(getUser(), "id");

    $query = "SELECT DISTINCT events.abbreviation as eventscode, events.name as eventsname, events.id as eventsid ";
    $query.= "FROM events,phase,hours ";
    $query.= "WHERE phase.id=hours.phaseid ";
    if (!empty($userid)) $query .= "AND userid='$userid' ";
    $query.= "AND phase.status='active' ";
    $query.= "AND events.status='active' ";
    $query.= "AND phase.eventsid=events.id ";
    $query.= "ORDER BY eventscode, eventsname";

    $arr = $db->getrows($query,'0','100');

    $newarr = Array();

    // For some reason, the above query returns double results (even though I
    // do a 'select distinct'!)
    // I fail to see why, but I'll work around it by checking for doubles.
    $alreadyhad = array();
    for ($i=0, $_i=count($arr); $i<$_i;$i++)
    {
      if (!in_array($arr[$i]['eventsid'], $alreadyhad))
      {
        $eventsid = $arr[$i]['eventsid'];
        $eventsdescriptor = empty($arr[$i]['eventscode']) ? $arr[$i]['eventsname'] : ($arr[$i]['eventscode'] . ": " . $arr[$i]['eventsname']);
        if (atk_strlen($eventsdescriptor) > $g_eventsnamesize)
          $eventsdescriptor = atk_substr($eventsdescriptor, 0, $g_eventsnamesize-2).".."; //update because of phases
        $newarr[] = array("eventsid"=>$eventsid, "eventsname"=>$eventsdescriptor);
        $alreadyhad[] = $eventsid;
      }
    }
    return $newarr;
  }

  /**
   * given a timestamp, this function calculates the weekstamp, which is a concatenation
   * of the year and the ISO week number. (e.g. 200134)
   */
  function weekstamp($timestamp)  // in achievotools.inc
  {
    /*
     * JN 02-06-26: FIX: Time locks based on week numbers not working on win32.
     *                   Reason is PHP: not all strftime functions are working on win32.
     *                   Solution: We have to calculate week of year manually.
     */

    $year = strftime("%Y",$timestamp);
    $yearStart = mktime(0,0,0,1,1,$year);
    $yearEnd = mktime(0,0,0,12,31,$year);

    $daysLost = strftime("%w",$yearStart);
    if ($daysLost > 4) {
      $daysLost -= 9;
    } else {
      $daysLost -= 2;
    }
    // $week = bcdiv(strftime("%j",$timestamp)+$daysLost+7,7,0);
    $week = "".floor((strftime("%j",$timestamp)+$daysLost+7)/7);

    /*
    atkdebug("(weekstamp): date: ".strftime("%a %d %m %Y",$timestamp).
             " week: ".$week.
             " day: ".strftime("%j",$timestamp).
             " jan1: ".strftime("%a",$yearStart).
             " dec31: ".strftime("%a",$yearEnd).
             " w1dLastY: ".($daysLost+1));
    */

    if ($week == 0) {
      //atkdebug("(weekstamp): adjust to previous year");
      return weekstamp(mktime(0,0,0,12,31,($year-1)));
    }

    if ($week == 53)
    {
      if ((strftime("%w", $yearEnd) >= 1) && (strftime("%w", $yearEnd)<= 3))
      {
        //atkdebug("(weekstamp): adjust to following year");
        return ($year+1)."01";
      }
    }

    return $year.sprintf("%02d", $week);
  }

  /*
   * Given a date in the form "2001-03-25", this function returns the date of the first
   * day (monday) of that week.
   * @deprecated use dateUtil::startOfWeek instead (note that it has a slightly different format)
   */
  function startOfWeek($date)
  {
    $viewtime = adodb_mktime(0,0,0,substr($date,5,2),substr($date,8,2),substr($date,0,4));
    $weekday = strftime("%w",$viewtime);
    if ($weekday==0) $weekday=7;
    return date("Y-m-d" ,$viewtime-(86400*($weekday-1)));
  }

  /*
   * Given a date in the form "2001-03-25", this function returns the date of the last
   * day (friday) of that week.
   * @deprecated use dateUtil::endOfWeek instead (note that it has a slightly different format)
   */
  function endOfWeek($date)
  {
    $viewtime = adodb_mktime(0,0,0,substr($date,5,2),substr($date,8,2),substr($date,0,4));
    $weekday = strftime("%w",$viewtime);
    if ($weekday==0) $weekday=7;
    return date("Y-m-d" ,$viewtime-(86400*($weekday-7)));
  }

  /**
   * Generic achievo mail function used when sending mails
   *
   * @param string/array $to Recipients e-mail address(es) (may not be empty, otherwise usermail fails and returns false)
   * @param string $subject Subject to be used when sending the mail (will be prefixed by [achievo notice], but may not be empty, otherwise usermail fails and returns false)
   * @param string $body Mail content
   * @param string $add_header SMTP Mail headers to be added to the mail
   * @return boolean True if succesfull, false if not
   */
  function usermail($to, $subject, $body, $add_header="")
  {
    // Determine the sender's name by using the mail_sender configuration variable
    $sender = atkconfig("mail_sender", "achievo");

    // If multiple recipients in array, then convert the recipients array to a comma seperated string
    if (is_array($to) && count($to)>0)
    {
      $to = implode(",", $to);
    }

    // If no recipient or subject found, dont attempt to sent
    if (($to=="") || ($subject==""))
    {
      atkdebug("No mail sent, missing to or subject");
      return false;
    }

    //Convert bare LF to CRLF (see: http://cr.yp.to/docs/smtplf.html)
    //First replace CRLF to LF, then replace all LF to CRLF. This must be done to
    //prevent replacing a CRLF with CRCRLF
    $body = preg_replace("/(\r\n)/", "\n", $body);
    $body = preg_replace("/(\n)/", "\r\n", $body);

    // Attempt to send the mail, and store the result in $result
    $result = mail($to, "[achievo notice] " . $subject, $body, "From: $sender\r\n" . $add_header);

    // Show debug info
    atkdebug($result ? "Sent mail to $to" : "Sending of mail to $to failed");

    // Use the mail result as return value
    return $result;
  }

  function time_format($time, $displayzero=false)
  {
    useattrib("atkdurationattribute");
    if ($time==0 && !$displayzero)
    {
      return "&nbsp;";
    }

    if(atkconfig("durationformat",0)==DURATIONFORMAT_DECIMAL)
    {
      $decimalvalue = floor(abs($time)/60) + (abs($time)%60)/60;
      $result = ($time<0?"-":"").sprintf("%02.02f", $decimalvalue);
    }
    elseif(atkconfig("durationformat",0)==DURATIONFORMAT_TIME)
    {
      $result = ($time<0?"-":"").floor(abs($time)/60).":".sprintf("%02d",(abs($time)%60));
    }

    return $result;
  }

?>