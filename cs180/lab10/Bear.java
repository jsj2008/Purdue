
public class Bear extends Animal{
	public Bear(String status) {
		super(status);
	}
	@Override
	public void makeMove(SiteGrid sg) {
		try {	
			if (getStatus().equals("ALIVE") && site.getType() == SiteType.WINTERING) {
				if ( Math.random() <= 0.3)
				die();
			}
			else super.makeMove(sg);
		}
		catch(Exception e) {
			super.makeMove(sg);
		}
	}
}
