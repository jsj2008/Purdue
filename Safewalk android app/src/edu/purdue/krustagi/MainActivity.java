package edu.purdue.krustagi;
/* 
 * @author Eehita Parameswaran (eparames@purdue.edu) Lab Section: LN1
 * @author Kush Rustagi (krustagi@purdue.edu) Lab Section: 806
 */
import android.annotation.SuppressLint;
import android.app.ActionBar;
import android.app.*;
import android.content.*;
import android.app.FragmentTransaction;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity implements SubmitCallbackListener,
		StartOverCallbackListener {
	/**
	 * The ClientFragment used by the activity.
	 */
	private ClientFragment clientFragment;

	/**
	 * The ServerFragment used by the activity.
	 */
	private ServerFragment serverFragment;

	/**
	 * UI component of the ActionBar used for navigation.
	 */
	private Button left;
	private Button right;
	private TextView title;

	/**
	 * Called once the activity is created.
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main_layout);

		this.clientFragment = ClientFragment.newInstance(this);
		this.serverFragment = ServerFragment.newInstance();

		FragmentTransaction ft = getFragmentManager().beginTransaction();
		ft.add(R.id.fl_main, this.clientFragment);
		ft.commit();
	}

	/**
	 * Creates the ActionBar: - Inflates the layout - Extracts the components
	 */
	@SuppressLint("InflateParams")
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		final ViewGroup actionBarLayout = (ViewGroup) getLayoutInflater()
				.inflate(R.layout.action_bar, null);

		// Set up the ActionBar
		final ActionBar actionBar = getActionBar();
		actionBar.setDisplayShowHomeEnabled(false);
		actionBar.setDisplayShowTitleEnabled(false);
		actionBar.setDisplayShowCustomEnabled(true);
		actionBar.setCustomView(actionBarLayout);

		// Extract the UI component.
		this.title = (TextView) actionBarLayout.findViewById(R.id.tv_title);
		this.left = (Button) actionBarLayout.findViewById(R.id.bu_left);
		this.right = (Button) actionBarLayout.findViewById(R.id.bu_right);
		this.right.setVisibility(View.INVISIBLE);

		return true;
	}

	/**
	 * Callback function called when the user click on the right button of the
	 * ActionBar.
	 * 
	 * @param v
	 */
	public void onRightClick(View v) {
		FragmentTransaction ft = getFragmentManager().beginTransaction();

		this.title.setText(this.getResources().getString(R.string.client));
		this.left.setVisibility(View.VISIBLE);
		this.right.setVisibility(View.INVISIBLE);
		ft.replace(R.id.fl_main, this.clientFragment);
		ft.commit();
	}

	/**
	 * Callback function called when the user click on the left button of the
	 * ActionBar.
	 * 
	 * @param v
	 */
	public void onLeftClick(View v) {
		FragmentTransaction ft = getFragmentManager().beginTransaction();

		this.title.setText(this.getResources().getString(R.string.server));
		this.left.setVisibility(View.INVISIBLE);
		this.right.setVisibility(View.VISIBLE);
		ft.replace(R.id.fl_main, this.serverFragment);
		ft.commit();

	}

	/**
	 * Callback function called when the user click on the submit button.
	 */
	String arr[] = new String[]{"CL50","EE","LWSN","PMU","PUSH"};
	boolean flag = true;
	int err;
	String str = "";
	@Override
	public void onSubmit() {
		// TODO: Get client info via client fragment
		String name = this.clientFragment.getName();
		int type = this.clientFragment.getType();
		String to = this.clientFragment.getTo();
		String from = this.clientFragment.getFrom();
		// Server info
		String host = this.serverFragment.getHost(getResources().getString(
				R.string.default_host));
		int port = this.serverFragment.getPort(Integer.parseInt(getResources()
				.getString(R.string.default_port)));
		// TODO: sanity check the results of the previous two dialogs
		String st = "";
		for (int i = 0; i < name.length(); i++) {
			if (name.charAt(i) == ',') {
				st += " - Name cannot have commas(,) \n";
				break;
			}
			if (name.equals("0")) {
				st += " - Name cannot be empty \n";
				break;
			}
		}
		if (from.equals(to))
			st += " - From has to be different from To \n";
		if (type == 2) {
			if (!(to.equals("*")))
				st += " - Volunteers must go to '*' \n";
		}
		//SERVER
		if (host.length() == 0)
			st += " - Host cannot be empty \n";
		for (int i = 0; i < host.length(); i ++) {
			String str3 = host.charAt(i) + "";
			if (str3.equals(" ")) {
				st += " - Host cannot contain spaces\n";
				break;
			}
		}
		if (port < 1 || port > 65535)
			st += " - Port has to be between 1 and 65535\n";
		if (!st.equals("")) {
			Error(st);
			return;
		}
		// TODO: Need to get command from client fragment
		
		String command = name + "," + from + "," + to + "," + type;

		FragmentTransaction ft = getFragmentManager().beginTransaction();

		this.title.setText(getResources().getString(R.string.match));
		this.left.setVisibility(View.INVISIBLE);
		this.right.setVisibility(View.INVISIBLE);

		// TODO: You may want additional parameters here if you tailor
		// the match fragment
		MatchFragment frag = MatchFragment.newInstance(this, host, port,
				command);

		ft.replace(R.id.fl_main, frag);
		ft.commit();
	}
	public void Error(String s) {
		AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(this);
		alertDialogBuilder.setMessage(s);
		alertDialogBuilder.setTitle("Errors");
		alertDialogBuilder.setNeutralButton("Okay", new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog,int id) {
						// if this button is clicked, just close
						// the dialog box and do nothing
						dialog.cancel();
					}
					});
 
		AlertDialog alertDialog = alertDialogBuilder.create();
		alertDialog.show();
	}

	/**
	 * Callback function call from MatchFragment when the user want to create a
	 * new request.
	 */
	@Override
	public void onStartOver() {
		this.clientFragment = ClientFragment.newInstance(this);
		onRightClick(null);
	}
	

}
