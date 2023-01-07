rm -rf /tmp/LSIM/
rm -rf CTestTestfile.cmake \
    lazy_debug_RangeLookUp.txt \
    libleveldb.a \
    Makefile \
    CMakeCache.txt \
    cmake_install.cmake \
    leveldbConfigVersion.cmake \
    main* \
    CMakeFiles \
    include \
    results_output.txt
cmake .. -DCMAKE_BUILD_TYPE=RELEASE -DNDEBUG_SWITCH=ON -DINTERNAL_TIMER_SWITCH=ON -DACCESS_PRIMARY_SWITCH=OFF
make -j
