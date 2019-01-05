<?php

/**
* Implementation of template preprocess for the view.
*/
function template_preprocess_views_views_gmap_plugin_style(&$vars) {
    $view           = &$vars['view'];
    $lat            = $vars['options']['lat'];//name of field used for lat
    $long           = $vars['options']['long'];//name of field used for long
    $popup_fields   = $vars['options']['popup_fields']; ////name of fields used for popup
    
    $c_lat          = $vars['options']['c_lat'];
    $c_long         = $vars['options']['c_long'];
    
    $map_width      = $vars['options']['map_width'];
    $map_height     = $vars['options']['map_height'];
    
    $vars['width']  = $map_width;
    $vars['height'] = $map_height;

    //unique id for the map
    $map_id = uniqid(); 
    $vars['map_id'] = $map_id;

    $markers = [];

    $api_key = variable_get('gmc_api_key');
    $api_key = $api_key?$api_key:'';

    if($api_key == '')
    {
        $config_link = l('Settings', '/admin/config/gmap/key', array(
            'query'=> ['destination'=>drupal_get_destination()['destination']]
        ));
        drupal_set_message('Google API key is not set. '.$config_link, 'warning');
    }
    
    foreach (array_keys($vars['rows']) as $key) {
        
        $marker = [];
        $marker['lat'] = $view->style_plugin->get_field($key, $lat); 
        $marker['long'] = $view->style_plugin->get_field($key, $long);
        
        $marker['popup_fields'] = "";
        foreach($popup_fields as $pkey=>$value)
        {
            if($value !== 0)
            {
                $marker['popup_fields'] .= $view->style_plugin->get_field($key, $pkey);
            }
        }
        
        $markers[] = $marker;
    }
    
    drupal_add_js("http://maps.google.com/maps/api/js?key={$api_key}&sensor=false", 'external');
 
    $makersJSON = json_encode($markers);
    $map_js = <<<ENDOFJS
 
        var locationJSON = {$makersJSON};
    
      var map = new google.maps.Map(document.getElementById('{$map_id}'), {
        zoom: 10,
        center: new google.maps.LatLng({$c_lat}, {$c_long}),
        mapTypeId: google.maps.MapTypeId.ROADMAP
      });
  
      var infowindow = new google.maps.InfoWindow();
  
      var marker, i;
  
      for (i = 0; i < locationJSON.length; i++) {  
        marker = new google.maps.Marker({
          position: new google.maps.LatLng(locationJSON[i].lat, locationJSON[i].long),
          map: map
        });
  
        google.maps.event.addListener(marker, 'click', (function(marker, i) {
          return function() {
            infowindow.setContent(locationJSON[i].popup_fields);
            infowindow.open(map, marker);
          }
        })(marker, i));
      }



ENDOFJS;



    drupal_add_js($map_js, array(
        'type' => 'inline',
        'scope' => 'footer',
        'weight' => 5,
      ));
    

}
