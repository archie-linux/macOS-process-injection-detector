CC = g++
CFLAGS = -Wall -Wextra -std=c++17
LIB_TARGET = libmalicious.dylib
APP_TARGET = test_app
DETECTOR_TARGET = detector

# Build all targets
all: $(LIB_TARGET) $(APP_TARGET) $(DETECTOR_TARGET)

# Build shared library
$(LIB_TARGET): libmalicious.cpp
	$(CC) -dynamiclib -o $@ $^

# Build test application
$(APP_TARGET): test_app.cpp
	$(CC) $(CFLAGS) -o $@ $^ -ldl

# Build detector
$(DETECTOR_TARGET): detector.cpp
	$(CC) $(CFLAGS) -o $@ $^

# Clean up generated files
clean:
	rm -f $(LIB_TARGET) $(APP_TARGET) $(DETECTOR_TARGET) detector_log.txt

