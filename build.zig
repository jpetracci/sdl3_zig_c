const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "sdl3_test",
        .target = target,
        .optimize = optimize,
    });
    exe.addCSourceFiles(.{
        .files = &.{
            "src/main.c",
        },
        .flags = &.{
            "-Wall",
            "-Werror",
        },
    });
    // link standard C library
    exe.linkLibC();

    // link SDL3
    const sdl_dep = b.dependency("sdl", .{
        .target = target,
        .optimize = optimize,
    });
    const sdl_lib = sdl_dep.artifact("SDL3");
    exe.root_module.linkLibrary(sdl_lib);

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
