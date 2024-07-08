First install the demo nodes package:

```
sudo apt install ros-${ROS_DISTRO}-demo-nodes-cpp
```

Then clone this package into a workspace and build it.

In one terminal window, run the demo service server:

```
ros2 run demo_nodes_cpp add_two_ints_server
```

In a second terminal window, run the node from this package:

```
ros2 run nesting_callbacks_demo client_node
```

You should see some console output from both the client and server nodes showing that the request is handled and the response is returned.
