# fgs_image_proc_node

ROS nodes for image processing.

# Executable files

- fgs_image_proc_node_simple_node

    Simple node.

    Subscribe then show the image.


    ```bash
    rosrun fgs_image_proc_node fgs_image_proc_node_simple_node /image_raw:=/image_topic_you_want_to_see
    ```

- fgs_image_proc_node_filter_node

    Filtering function added in simple node.

    You can change parameter of filter by using rqt_reconfigure

    ```bash
    rosrun fgs_image_proc_node fgs_image_proc_node_filter_node /image_raw:=/image_topic_you_want_to_see _filter/type:=gaussian
    rosrun rqt_reconfigure rqt_reconfigure
    ```
