<?php
// $Id$

/**
 * @file
 * Administration page callbacks for the annotate module.
 */

/** 
 * Define the form for subscribe to content. 
 */ 
 
 
function subscription_form($uid) {
	global $user;
	
	//dpm($uid);
	//dpm($user);
	//return t('test');
  
	//$output = t('This page contains our example form.');
  $output .= drupal_get_form('subscriptions_entry_form');
  return $output;	
	
	//subscriptions_entry_form
}



function subscriptions_entry_form() {
  // Define a fieldset.
  //$form['annotate'] = array( 
   // '#type' => 'fieldset', 
    //'#title' => t('Annotations') 
 // ); 
  
  // Get an array of node types with internal names as keys and
  // "friendly names" as values. E.g.,
  // array('page' => 'Page', 'story' => 'Story')
  $options = node_get_types('names');
  $subcsription_types = array(
		'cc_content' => t('Corporate Communications'),
		'fa_content' => t('Finance'), 
		'hr_content' => t('HR'), 
		'it_content' => t('IT'), 
		'ms_content' => t('Marketing & Sales'), 
		'pmcgroup_content' => t('PMCnet Startpages'), 
		'products_content' => t('Products'), 
		'pis_content' => t('Purchase Indirect & Services'), 
		'pl_content' => t('Purchasing & Logistics'), 
		'qlikview_content' => t('Qlikview'),
		'qe_content' => t('Quality & Environmental'),
		'tech_content' => t('Technology'),
		'vacancy' => t('Vacancy'), 
		'news_content' => t('News & Info'),
		'note_content' => t('Notes'),    
	);
  //var_dump($subcsription_types);
  //var_dump(array_intersect_key($subcsription_types, $options));
  //var_dump(array_intersect($subcsription_types, $options)); 
  //dpm($options);
  $form['subscribed_node_types'][nodetypes] = array( 
    '#type' => 'checkboxes', 
    '#title' => t('You may subscribe to the following content'), 
    '#options' => array_intersect_key($subcsription_types, $options), 
    //'#default_value' => get_subscriptions(), 
	'#default_value' => get_subscriptions(), 
    '#description' => t(''), 
	'#weight' => 10,	
  ); 
  
  // Define a submit button.
  $form['subscribed_node_types']['submit'] = array( 
    '#type' => 'submit', 
    '#value' => t('Save'),
	'#weight' => 20, 
  ); 
  //dpm($form);
  return $form; 
} 

/**
 * Handle submission of the annotation form and saving
 * of the data to the database.
 */
function subscriptions_entry_form_submit($form, $form_state) {
  global $user;
  $subscribed_content = $form_state['values']['nodetypes'];
  //dpm($subscribed_content);
  db_query("DELETE FROM {subscriptions} WHERE uid = %d", $user->uid);
  if (isset($subscribed_content)) {
    foreach($subscribed_content as $key => $value){
      if (is_string($value)) {
        db_query("INSERT INTO {subscriptions} (uid, contenttype, created) VALUES (%d, '%s', %d)", $user->uid, $value, time() + 3600);
	  }
	}
  drupal_set_message(t('Your settings where saved'));	
  }  
}

function get_subscriptions() {
  global $user;
  $contenttypes = array();
  $result = db_query("SELECT contenttype FROM {subscriptions} WHERE uid = %d", $user->uid);
  while($row = mysqli_fetch_array($result)) {
	$contenttypes[] = $row[0];
  }
  return $contenttypes;
}