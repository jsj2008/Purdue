
public class Bird extends Animal{
	public Bird(String status) {
		super(status);
	}
	@Override
	public void makeMove(SiteGrid sg) {
		try {
		if (getStatus().equals("ALIVE") && site.getType() == SiteType.WINTERING) {
			die();
		}
		else super.makeMove(sg);
		}
		catch(Exception e) {
			super.makeMove(sg);
		}
	}
}
