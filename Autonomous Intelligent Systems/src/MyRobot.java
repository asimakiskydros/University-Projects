import javax.vecmath.Vector3d;
import simbad.sim.*;

public class MyRobot extends Agent {
    LightSensor left;
    LightSensor right;
    LightSensor center;
    RangeSensorBelt sonars;
    iBug algorithm;

    public MyRobot (Vector3d position, String name) {
        super(position,name);
        this.left = RobotFactory.addLightSensor(this, new Vector3d(0.6,0.47,-0.6), 0, "left");
        this.right = RobotFactory.addLightSensor(this, new Vector3d(0.6,0.47,0.6), 0, "right");
        this.center = RobotFactory.addLightSensor(this, new Vector3d(0,0.47,0), 0, "center");
        this.sonars = RobotFactory.addSonarBeltSensor(this, 12);
    }
    public void initBehavior(){
        this.algorithm = new iBug(this, this.sonars, this.left, this.right, this.center);
    }
    public void performBehavior(){ this.algorithm.step(); }
}
