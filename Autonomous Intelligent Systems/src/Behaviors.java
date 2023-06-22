import javax.vecmath.*;
import simbad.sim.*;

public class Behaviors {
    static double SAFETY = 1;

    /**
     * Wraps the given angle in the [-2pi, 2pi] range.
     * @param angle the original angle
     * @return the above angle inside [-2pi, 2pi]
     * @author dvrakas
     */
    private static double wrap2pi(double angle){
        if (angle > Math.PI)
            return angle - 2 * Math.PI;
        if (angle <= -Math.PI)
            return angle + 2 * Math.PI;
        return angle;
    }

    /**
     * Calculates the point the robot must reach in order to perform orbiting.
     * @param robot the guided robot
     * @param sonars the robot's sonars
     * @param minSonar the minimizer of the sonar readings
     * @return the sensed point to follow for orbiting
     * @author dvrakas
     */
    private static Point3d sensedPoint(Agent robot, RangeSensorBelt sonars, int minSonar){
        double v = robot.getRadius();
        if (sonars.hasHit(minSonar))
            v += sonars.getMeasurement(minSonar);
        else
            v += sonars.getMaxRange();
        double x = v*Math.cos(sonars.getSensorAngle(minSonar));
        double z = v*Math.sin(sonars.getSensorAngle(minSonar));
        return new Point3d(x,0,z);
    }

    /**
     * Decide whether the robot is dangerously close to an object.
     * @param sonars the robot's sonars
     * @return True if the robot has "bumped" i.e. it's too close to an object
     * @author kasimakis
     */
    public static boolean hasBumped(RangeSensorBelt sonars){
        for (int i = 0; i < sonars.getNumSensors(); i++)
            // take into consideration only those sonars that are in
            // the front quarter-circle of the robot
            if (Math.abs(sonars.getSensorAngle(i)) < Math.PI * 0.25
                    && sonars.getMeasurement(i) < SAFETY)
                return true;
        return false;
    }

    /**
     * Halt robot movement when called.
     * @param robot the guided robot
     * @author kasimakis, tonyloudis
     */
    public static void halt(Agent robot){
        robot.setTranslationalVelocity(0);
        robot.setRotationalVelocity(0);
    }

    /**
     * Correct alignment and go towards the light when called.
     * @param robot the guided robot
     * @param left the left light sensor's reading
     * @param right the right light sensor's reading
     * @param center the center light sensor's reading
     * @author kasimakis, tonyloudis
     */
    public static void march(Agent robot, double left, double right, double center){
        double K1 = 2, K2 = 150;
        // as you get closer to the target, slow down
        robot.setTranslationalVelocity(K1 / (1 + center));
        // correct alignment with the light,
        // becoming less aggressive about it on each iteration
        robot.setRotationalVelocity(K2 * (left - right));
    }

    /**
     * Orbit the nearest object when called.
     * Slightly changed to only work counter clock wise (as dictated by iBug).
     * @param robot the guided robot
     * @param sonars the robot's sonars
     * @author dvrakas
     */
    public static void orbit(Agent robot, RangeSensorBelt sonars){
        double K1 = 2, K2 = 0.8, K3 = 1;
        int minSonar = 0;
        for (int i = 0; i < sonars.getNumSensors(); i++)
            if (sonars.getMeasurement(i) < sonars.getMeasurement(minSonar))
                minSonar = i;
        Point3d iH = sensedPoint(robot, sonars, minSonar);
        Vector3d vec = new Vector3d(iH.z, 0, -iH.x);
        double distance = iH.distance(new Point3d(0, 0, 0));
        double phi = wrap2pi(Math.atan(K3 * (distance - SAFETY)) + Math.atan2(vec.z, vec.x));
        robot.setRotationalVelocity(K1 * phi);
        robot.setTranslationalVelocity(K2 * Math.cos(phi));
    }
}
