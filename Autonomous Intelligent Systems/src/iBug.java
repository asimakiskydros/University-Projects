import simbad.sim.*;

public class iBug {
    Agent robot;
    LightSensor left, right, center;
    RangeSensorBelt sonars;
    double globalMax = 0.78;
    double localMax = 0;

    public iBug(
            Agent robot, RangeSensorBelt sonars, LightSensor left,
            LightSensor right, LightSensor center
    ){
        this.robot = robot;
        this.sonars = sonars;
        this.left = left;
        this.right = right;
        this.center = center;
    }

    /**
     * 1) Get all sensor readings
     * 2) Perform the first eligible action with the following left2right priority:
     *      halt, orbit, record local max, align and march.
     * This should simulate iBug's function.
     * @author kasimakis, tonyloudis
     */
    public void step(){
        // get luminance readings
        double l = Math.pow(this.left.getLux(), 0.1);
        double r = Math.pow(this.right.getLux(), 0.1);
        double c = Math.pow(this.center.getLux(), 0.1);
        // get front sonars reading
        boolean bumped = Behaviors.hasBumped(this.sonars);

        // halt if the read luminance peaks above the global max
        if (c >= this.globalMax)
            Behaviors.halt(this.robot);
        // as long as the current local max isn't exceeded, orbit
        else if (c < this.localMax)
            Behaviors.orbit(this.robot, this.sonars);
        // if the robot has bumped, initialize orbiting
        else if (bumped)
            this.localMax = c;
        // align and walk to goal
        else
            Behaviors.march(this.robot, l, r, c);

    }

}

