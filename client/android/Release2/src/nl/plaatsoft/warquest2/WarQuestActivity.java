package nl.plaatsoft.warquest2;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import nl.plaatsoft.warquest2.R;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.Window;
import android.webkit.CookieManager;
import android.webkit.CookieSyncManager;
import android.webkit.WebChromeClient;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Toast;

public class WarQuestActivity extends Activity {
	
	WebView browser;
	SharedPreferences preferences;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        boolean network=false;
        ConnectivityManager manager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo[] info = manager.getAllNetworkInfo();
        for (int i=0; i<info.length; i++) {
        	network=info[i].isConnected();
        	if (network==true) break;
        }
        
        if (!network) {
        	
        	 Context ctx = getApplicationContext();
             CharSequence txt = getString(R.string.internet_down);
             int duration = Toast.LENGTH_LONG;
             Toast toast = Toast.makeText(ctx, txt, duration);
             toast.show();
             
             return;	
        } 
        
        // Adds Progress bar Support
        this.getWindow().requestFeature(Window.FEATURE_PROGRESS);
        setContentView(R.layout.main );
        
        preferences = PreferenceManager.getDefaultSharedPreferences(this);
        String username = preferences.getString("username", "");
		String password = preferences.getString("password", "");
		Boolean login = preferences.getBoolean("login", true);
		
		Map<String,String> headers = new HashMap<String, String>();
		if (login) {
			
			// Auto sign-on
			if ((username.length()==0) && (password.length()==0)) {
			
				// Create unique username / password if user not exiting 		      	
				DateFormat dfm = new SimpleDateFormat("yyyyMMddHHmmss0");
				username = dfm.format(new Date());
				password = username;
				SharedPreferences.Editor editor = preferences.edit();
				editor.putString("username", username); 
				editor.putString("password", password); 
				editor.putBoolean("login", true); 
				editor.commit();
			
				// Register and login afterwards
				headers.put("eid", "5");
			
			} else {
		
				// Login direct in with existing account
				headers.put("eid", "1");
			}
			headers.put("username", username);
			headers.put("password", password);
		}
		
        headers.put("version", getString(R.string.app_version));
        
        // Makes Progress bar Visible
        getWindow().setFeatureInt( Window.FEATURE_PROGRESS, Window.PROGRESS_VISIBILITY_ON);

        // Remove old cookies to force new login (after restart)
        CookieSyncManager.createInstance(this); 
        CookieManager cookieManager = CookieManager.getInstance();
        cookieManager.removeAllCookie();

       
        browser=(WebView)findViewById(R.id.webkit);
        
        browser.loadUrl(getString(R.string.url), headers);
        //browser.loadUrl("http://10.0.2.2/warquest", headers);
       
        browser.getSettings().setJavaScriptEnabled(true);

        browser.getSettings().setLoadWithOverviewMode(true);
        
        // Auto Scale HTML page.
        browser.getSettings().setUseWideViewPort(true);
       
        browser.setWebViewClient(new WarQuestWebViewClient());
        
		 // Sets the Chrome Client, and defines the onProgressChanged
	     // This makes the Progress bar be updated.
	     final Activity MyActivity = this;
	     
	     MyActivity.setTitle(R.string.app_name);
	  
	     browser.setWebChromeClient(new WebChromeClient() {
	     
	    	 public void onProgressChanged(WebView view, int progress)  {
	    		 //Make the bar disappear after URL is loaded, and changes string to Loading...
	    		 if ((browser.getTitle()!=null) && (browser.getTitle().length()>0)) {
	    			 MyActivity.setTitle(browser.getTitle());
	    		 } else { 
	    			 MyActivity.setTitle(R.string.app_name);
	    		 }
	    		 MyActivity.setProgress(progress * 100); //Make the bar disappear after URL is loaded
	    	 	}
	        });
    }
    
  
    @Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.menu, menu);
		return true;
	}
    
    @Override
	public boolean onOptionsItemSelected(MenuItem item) {
    	
        switch(item.getItemId())
        {
        	case R.id.exit:
        		// On exit clean all caches to prevent trash in cache.
        		if (browser != null) {
        			browser.clearHistory();
        			browser.clearFormData();
        			browser.clearCache(true);
        		}
     
        		this.finish();
        		System.exit(0);
        		return true;
        
        	case R.id.settings:		
        		// Launch Setting Window
    			Intent i = new Intent( WarQuestActivity.this, SettingsActivity.class);
    			startActivity(i);
        		return true;
        
        	case R.id.about:
        		// Launch Setting Window
    			Intent j = new Intent( WarQuestActivity.this, AboutActivity.class);
    			startActivity(j);
        		return true;
        }
        return super.onOptionsItemSelected(item);
	}
    
    private class WarQuestWebViewClient extends WebViewClient {
        @Override
        public boolean shouldOverrideUrlLoading(WebView view, String url) {
            view.loadUrl(url);
            return true;
        }
    }
    
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
        	
        	browser.goBack();
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }
}