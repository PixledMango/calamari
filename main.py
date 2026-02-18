import pybullet
import time
import pybullet_data

physicsClient = pybullet.connect(pybullet.GUI)
pybullet.setAdditionalSearchPath(pybullet_data.getDataPath())
pybullet.setGravity(0,0,-10)

planeId = pybullet.loadURDF("plane.urdf")
startPos = [0,0,1]
startOrientation = pybullet.getQuaternionFromEuler([0,0,0])
boxId = pybullet.loadURDF("./r2d2.urdf", startPos, startOrientation, useFixedBase=False)

for i in range (10000):
    pybullet.stepSimulation()
    time.sleep(1./240.)
cubePos, cubeOrn = pybullet.getBasePositionAndOrientation(boxId)
print(cubePos, cubeOrn)
pybullet.disconnect()



